// AudioUnit code is based on auv3test5
// Created by Ronald Nicholson on 7/31/17.
// Copyright © 2017 HotPaw Productions.
// Distribution under the BSD 2-clause license

// Wrapper © 2023 Alex nadzharov

#include "RNBO.h"

#import "RNBOAudioUnit.h"

#include <fstream>
#include <iostream>
#include <memory>

#import <AudioToolbox/AudioToolbox.h>
#import "RNBOExtensionBufferedAudioBus.hpp"

long int toneCount = 1;
float testFrequency = 880.0; // an audio frequency in Hz
float testVolume = 0.5; // volume setting
double sampleRateHz = 44100.0;

@interface RNBOAudioUnit ()
@property AUAudioUnitBusArray *outputBusArray;
@property AUAudioUnitBusArray *inputBusArray;
@property (nonatomic, readonly) AUAudioUnitBus *outputBus;
@end

@implementation RNBOAudioUnit { // an eXperimental V3 AudioUnit
    // float            frequency;
//    AudioBufferList const *myAudioBufferList;
//    AVAudioPCMBuffer *my_pcmBuffer;
//    AUAudioUnitBus *outputBus;
//    AUAudioUnitBus *inputBus;
    BufferedInputBus _inputBus;
    std::unique_ptr<RNBO::CoreObject> _object;
}

// @synthesize parameterTree;
//@synthesize outputBusArray;
//@synthesize inputBusArray;

- (instancetype)initWithComponentDescription:(AudioComponentDescription)componentDescription
                options						:(AudioComponentInstantiationOptions)options
                error						:(NSError **)outError
{
    self = [super	initWithComponentDescription:componentDescription
                    options						:options
                    error						:outError];

    if (self == nil) {
        return nil;
    }

    AVAudioFormat *defaultFormat = [[AVAudioFormat alloc]
                                    initStandardFormatWithSampleRate:sampleRateHz
                                    channels						:2];

    outputBus = [[AUAudioUnitBus alloc] initWithFormat:defaultFormat error:nil];
    outputBusArray = [[AUAudioUnitBusArray alloc]	initWithAudioUnit	:self
                                                    busType				:AUAudioUnitBusTypeOutput
                                                    busses				:@[ outputBus ]];

    _inputBus.init(defaultFormat, 8);
    inputBusArray = [[AUAudioUnitBusArray alloc]	initWithAudioUnit	:self
                                                    busType				:AUAudioUnitBusTypeOutput
                                                    busses				:@[ _inputBus.bus ]];

    self.maximumFramesToRender = 512;

    // our
    _object.reset(new RNBO::CoreObject());
    _object->prepareToProcess(44100, 64);

    //
    [self loadFileDependencies];

    return self;
}

- (AUAudioUnitBusArray *)outputBusses
{
    return _outputBusArray;
}

- (AUAudioUnitBusArray *)inputBusses
{
    return _inputBusArray;
}

- (BOOL)allocateRenderResourcesAndReturnError:(NSError **)outError
{
    if (![super allocateRenderResourcesAndReturnError:outError]) {
        return NO;
    }

    _inputBus.allocateRenderResources(self.maximumFramesToRender);
    my_pcmBuffer = [[AVAudioPCMBuffer alloc]	initWithPCMFormat	:outputBus.format
                                                frameCapacity		:4096];
    myAudioBufferList = my_pcmBuffer.audioBufferList;

    _object->prepareToProcess(44100, 4096);

    return YES;
}

- (void)deallocateRenderResources
{
    [super deallocateRenderResources];
}

// sometimes the buffers come back nil, so fix them
void repairOutputBufferList(AudioBufferList			*outBufferList,
                            AVAudioFrameCount		frameCount,
                            bool					zeroFill,
                            AudioBufferList const	*myAudioBufferList) {
    UInt32 byteSize = frameCount * sizeof(float);
    int numberOfOutputBuffers = outBufferList->mNumberBuffers;

    if (numberOfOutputBuffers > 2) {
        numberOfOutputBuffers = 2;
    }

    for (int i = 0; i < numberOfOutputBuffers; ++i) {
        outBufferList->mBuffers[i].mNumberChannels = myAudioBufferList->mBuffers[i].mNumberChannels;
        outBufferList->mBuffers[i].mDataByteSize = byteSize; // set buffer size

        if (outBufferList->mBuffers[i].mData == NULL) { // copy buffer pointers if needed
            outBufferList->mBuffers[i].mData = myAudioBufferList->mBuffers[i].mData;
        }

        if (zeroFill) {
            memset(outBufferList->mBuffers[i].mData, 0, byteSize);
        }
    }
}

#pragma mark - AUAudioUnit (AUAudioUnitImplementation)

- (AUInternalRenderBlock)internalRenderBlock {
    /*
       Capture in locals to avoid ObjC member lookups. If "self" is captured in
       render, we're doing it wrong.
     */
    // Specify captured objects are mutable.
    __block std::unique_ptr<RNBO::CoreObject> &object = _object;
    __block BufferedInputBus *input = &_inputBus;

    return ^AUAudioUnitStatus (AudioUnitRenderActionFlags *actionFlags,
                               const AudioTimeStamp *timestamp,
                               AVAudioFrameCount frameCount,
                               NSInteger outputBusNumber,
                               AudioBufferList *outputData,
                               const AURenderEvent *realtimeEventListHead,
                               AURenderPullInputBlock pullInputBlock) {
               AudioBufferList *inAudioBufferList = input->mutableAudioBufferList;
               AudioBufferList *outAudioBufferList = outputData;

               /*
                  Important:
                  If the caller passed non-null output pointers (outputData->mBuffers[x].mData), use those.

                  If the caller passed null output buffer pointers, process in memory owned by the Audio Unit
                  and modify the (outputData->mBuffers[x].mData) pointers to point to this owned memory.
                  The Audio Unit is responsible for preserving the validity of this memory until the next call to render,
                  or deallocateRenderResources is called.

                  If your algorithm cannot process in-place, you will need to preallocate an output buffer
                  and use it here.

                  See the description of the canProcessInPlace property.
                */

               // If passed null output buffer pointers, process in-place in the input buffer.

               if (outAudioBufferList->mBuffers[0].mData == nullptr) {
                   for (UInt32 i = 0; i < outAudioBufferList->mNumberBuffers; ++i) {
                       outAudioBufferList->mBuffers[i].mData = inAudioBufferList->mBuffers[i].mData;
                   }
               }

               int numInputBuffers = inAudioBufferList->mNumberBuffers;

               float *inLeft = (float *)inAudioBufferList->mBuffers[0].mData;
               float *inRight = (float *)inAudioBufferList->mBuffers[1].mData;
//
//               if (numInputBuffers == 0) {
//                   inRight = (float *)inAudioBufferList->mBuffers[1].mData;
//               }

               float *inputBuffer[numInputBuffers];
               inputBuffer[0] = inLeft;
               inputBuffer[1] = inRight;

               int numOutputBuffers = outAudioBufferList->mNumberBuffers;

               float *outLeft = (float *)outAudioBufferList->mBuffers[0].mData;
               float *outRight = NULL;

               if (numOutputBuffers == 2) {
                   outRight = (float *)outAudioBufferList->mBuffers[1].mData;
               }

               float *outputBuffer[numOutputBuffers];
               outputBuffer[0] = outLeft;
               outputBuffer[1] = outRight;

               // ========== Actual process =========
               object->process(inputBuffer, numInputBuffers, outputBuffer, numOutputBuffers, frameCount);
               // ========== Actual process =========
               return noErr;
    };
}

#pragma mark - Parameters


- (void)setParameterValue:(size_t)number value:(float)v
{
    @synchronized(self) {
        self->_object->setParameterValue(number, v);
    }
}

- (void)setParameterValueNormalized:(size_t)number valueNormalized:(float)v
{
    @synchronized(self) {
        self->_object->setParameterValueNormalized(number, v);
    }
}

- (size_t)getParameterCount
{
    @synchronized(self) {
        return self->_object->getNumParameters();
    }
}

- (float)getParameterValue:(size_t)number
{
    @synchronized(self) {
        return self->_object->getParameterValue(number);
    }
}

- (float)getParameterInitialValue:(size_t)number
{
    @synchronized(self) {
        RNBO::ParameterInfo info;
        self->_object->getParameterInfo(number, &info);
        return info.initialValue;
    }
}

- (float)getParameterMin:(size_t)number
{
    @synchronized(self) {
        RNBO::ParameterInfo info;
        self->_object->getParameterInfo(number, &info);
        return info.min;
    }
}

- (float)getParameterMax:(size_t)number
{
    @synchronized(self) {
        RNBO::ParameterInfo info;
        self->_object->getParameterInfo(number, &info);
        return info.max;
    }
}

- (float)getParameterExponent:(size_t)number
{
    @synchronized(self) {
        RNBO::ParameterInfo info;
        self->_object->getParameterInfo(number, &info);
        return info.exponent;
    }
}

- (int)getParameterSteps:(size_t)number
{
    @synchronized(self) {
        RNBO::ParameterInfo info;
        self->_object->getParameterInfo(number, &info);
        return info.steps;
    }
}

- (NSString *)getParameterUnit:(size_t)number
{
    @synchronized(self) {
        RNBO::ParameterInfo info;
        self->_object->getParameterInfo(number, &info);
        return [NSString stringWithFormat:@"%s", info.unit];
    }
}

- (NSString *)getParameterDisplayName:(size_t)number
{
    @synchronized(self) {
        RNBO::ParameterInfo info;
        self->_object->getParameterInfo(number, &info);
        return [NSString stringWithFormat:@"%s", info.displayName];
    }
}

#pragma mark -
#pragma mark file loader

CFURLRef _getFileUrl(const std::string& filepath) {
    NSString *filePathNSString = [NSString stringWithFormat:@"%s", filepath.c_str()];
    CFURLRef cfUrl = CFBundleCopyResourceURL(CFBundleGetMainBundle(), (__bridge CFStringRef)(filePathNSString), NULL, NULL);

    return cfUrl;
}

std::string _getStringFrom(CFURLRef cfUrl) {
    char *buf = new char[1024];

    CFURLGetFileSystemRepresentation(cfUrl, false, (uint8_t *)buf, 1024); //(NSString*)CFURLGet(cfUrl);
    std::string fullPath = std::string(buf);

    return fullPath;
}

- (void)loadFileDependencies
{
    using namespace RNBO;

    // Read in the dependencies.json file as a std::string

    auto dependenciesFileName = "dependencies.json";
    auto fullDependenciesFileName = _getStringFrom(_getFileUrl(dependenciesFileName));

    std::ifstream t(fullDependenciesFileName);

    if (!t.is_open()) {
        std::cout << "ERROR: failed to open " << fullDependenciesFileName << std::endl;
        return;
    }

    // read json
    std::stringstream buffer;
    buffer << t.rdbuf();

    // Parse dependencies into a RNBO DataRefList
    DataRefList list(buffer.str());

    // Loop and load
    for (int i = 0; i < list.size(); i++) {
        // Get parsed info about this data reference
        std::string idstr = list.datarefIdAtIndex(i);
        DataRefType type = list.datarefTypeAtIndex(i);
        std::string location = list.datarefLocationAtIndex(i);

        // The type can be either URL or File
        if (type == DataRefType::File) {
            std::cout << "--- buffer id: " << idstr << "\n";
            std::cout << "--- file path: " << list.datarefLocationAtIndex(i) << "\n";

            std::string filepath = list.datarefLocationAtIndex(i);

            auto cfUrl = _getFileUrl(filepath);
            auto fullPath = _getStringFrom(cfUrl);

            std::cout << "--- full file path: " << fullPath << std::endl;

            AudioFileID audioFile;

            AudioFileOpenURL(cfUrl, kAudioFileReadPermission, 0, &audioFile);
            CFBridgingRelease(cfUrl);

            if (!audioFile) {
                std::cout << "ERROR: failed to read audio file: " << filepath << std::endl;
                return;
            }

            AudioStreamBasicDescription audioFormat {};
            uint32_t size_af = {
                sizeof(audioFormat)
            };
            AudioFileGetProperty(audioFile, kAudioFilePropertyDataFormat, &size_af, &audioFormat);

            uint64_t dataSize {
                0
            };
            uint32_t size_ds {
                sizeof(dataSize)
            };
            AudioFileGetProperty(audioFile, kAudioFilePropertyAudioDataByteCount, &size_ds, &dataSize);

            auto channels = audioFormat.mChannelsPerFrame;
            auto samplerate = audioFormat.mSampleRate;
            auto sampleFormat = audioFormat.mBitsPerChannel;
            auto bigEndian = audioFormat.mFormatFlags | kAudioFormatFlagIsBigEndian;

            if (dataSize > (1LL << 32)) {
                std::cout << "WARNING: reading file larger than 4GB is not yet supported; reading first 4GB" << std::endl;
            }

            uint32_t frames = (uint32_t)((dataSize < (1LL << 32)) ? dataSize : ((1LL << 32) - 1));

            RNBO::Float32AudioBuffer bufferType(channels, samplerate);

            // Make space to store the file
            const uint32_t sampleBufferSize = sizeof(float) * frames * channels;
            float *sampleBuffer = (float *)malloc(sampleBufferSize);

            // import 16-bit
            if (sampleFormat == 16) {
                struct Data {
                    char b1 {
                        0
                    };
                    char b2 {
                        0
                    };
                };
                const auto getData = [](const Data& d, const bool& b)->int16_t {
                    if (!b) {
                        return d.b1 + (d.b2 << 8);
                    } else {
                        return d.b2 + (d.b1 << 8);
                    }
                };

                std::vector<Data> rawBuffer {};
                rawBuffer.resize(frames);

                AudioFileReadBytes(audioFile, false, 0, &frames, rawBuffer.data());

                size_t i = 0;

                for (auto& e : rawBuffer) {
                    sampleBuffer[i++] = (float(getData(e, bigEndian))) / 32768.;
                }
            }

            AudioFileClose(audioFile);

            _object->setExternalData(
                idstr.c_str(),
                (char *)sampleBuffer,
                frames * sizeof(float) / sizeof(char),
                bufferType,
                [](RNBO::ExternalDataId id, char *data) {
                std::cout	<< "--- Buffer freed"
                            << "\n";
                free(data);
            });
            std::cout << "--- Success: Read " << frames << " samples (" << dataSize << ") from file " << filepath << "\n";
        }
    }
}

- (void)setParameterValue:(size_t)number valueNormalized:(float)v {
}

@end

// eof

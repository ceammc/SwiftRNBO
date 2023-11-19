/*******************************************************************************************************************
Copyright (c) 2023 Cycling '74

The code that Max generates automatically and that end users are capable of
exporting and using, and any associated documentation files (the “Software”)
is a work of authorship for which Cycling '74 is the author and owner for
copyright purposes.

This Software is dual-licensed either under the terms of the Cycling '74
License for Max-Generated Code for Export, or alternatively under the terms
of the General Public License (GPL) Version 3. You may use the Software
according to either of these licenses as it is most appropriate for your
project on a case-by-case basis (proprietary or not).

A) Cycling '74 License for Max-Generated Code for Export

A license is hereby granted, free of charge, to any person obtaining a copy
of the Software (“Licensee”) to use, copy, modify, merge, publish, and
distribute copies of the Software, and to permit persons to whom the Software
is furnished to do so, subject to the following conditions:

The Software is licensed to Licensee for all uses that do not include the sale,
sublicensing, or commercial distribution of software that incorporates this
source code. This means that the Licensee is free to use this software for
educational, research, and prototyping purposes, to create musical or other
creative works with software that incorporates this source code, or any other
use that does not constitute selling software that makes use of this source
code. Commercial distribution also includes the packaging of free software with
other paid software, hardware, or software-provided commercial services.

For entities with UNDER $200k in annual revenue or funding, a license is hereby
granted, free of charge, for the sale, sublicensing, or commercial distribution
of software that incorporates this source code, for as long as the entity's
annual revenue remains below $200k annual revenue or funding.

For entities with OVER $200k in annual revenue or funding interested in the
sale, sublicensing, or commercial distribution of software that incorporates
this source code, please send inquiries to licensing@cycling74.com.

The above copyright notice and this license shall be included in all copies or
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

Please see
https://support.cycling74.com/hc/en-us/articles/10730637742483-RNBO-Export-Licensing-FAQ
for additional information

B) General Public License Version 3 (GPLv3)
Details of the GPLv3 license can be found at: https://www.gnu.org/licenses/gpl-3.0.html
*******************************************************************************************************************/

#include "RNBO_Common.h"
#include "RNBO_AudioSignal.h"

namespace RNBO {


#define trunc(x) ((Int)(x))

#if defined(__GNUC__) || defined(__clang__)
    #define RNBO_RESTRICT __restrict__
#elif defined(_MSC_VER)
    #define RNBO_RESTRICT __restrict
#endif

#define FIXEDSIZEARRAYINIT(...) { }

class rnbomatic : public PatcherInterfaceImpl {
public:

class RNBOSubpatcher_84 : public PatcherInterfaceImpl {
    
    friend class rnbomatic;
    
    public:
    
    RNBOSubpatcher_84()
    {
    }
    
    ~RNBOSubpatcher_84()
    {
    }
    
    virtual rnbomatic* getPatcher() const {
        return static_cast<rnbomatic *>(_parentPatcher);
    }
    
    rnbomatic* getTopLevelPatcher() {
        return this->getPatcher()->getTopLevelPatcher();
    }
    
    void cancelClockEvents()
    {
    }
    
    Index getNumMidiInputPorts() const {
        return 0;
    }
    
    void processMidiEvent(MillisecondTime , int , ConstByteArray , Index ) {}
    
    Index getNumMidiOutputPorts() const {
        return 0;
    }
    
    void process(
        const SampleValue * const* inputs,
        Index numInputs,
        SampleValue * const* outputs,
        Index numOutputs,
        Index n
    ) {
        this->vs = n;
        this->updateTime(this->getEngine()->getCurrentTime());
        SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
        SampleValue * out2 = (numOutputs >= 2 && outputs[1] ? outputs[1] : this->dummyBuffer);
        const SampleValue * in1 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
        const SampleValue * in2 = (numInputs >= 2 && inputs[1] ? inputs[1] : this->zeroBuffer);
        this->lores_01_perform(this->lores_01_cutoff, this->lores_01_resonance, in1, out1, n);
        this->lores_02_perform(this->lores_02_cutoff, this->lores_02_resonance, in2, out2, n);
        this->stackprotect_perform(n);
        this->audioProcessSampleCount += this->vs;
    }
    
    void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
        if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
            this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
            this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
            this->didAllocateSignals = true;
        }
    
        const bool sampleRateChanged = sampleRate != this->sr;
        const bool maxvsChanged = maxBlockSize != this->maxvs;
        const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;
    
        if (sampleRateChanged || maxvsChanged) {
            this->vs = maxBlockSize;
            this->maxvs = maxBlockSize;
            this->sr = sampleRate;
            this->invsr = 1 / sampleRate;
        }
    
        this->lores_01_dspsetup(forceDSPSetup);
        this->lores_02_dspsetup(forceDSPSetup);
    
        if (sampleRateChanged)
            this->onSampleRateChanged(sampleRate);
    }
    
    void setProbingTarget(MessageTag id) {
        switch (id) {
        default:
            {
            this->setProbingIndex(-1);
            break;
            }
        }
    }
    
    void setProbingIndex(ProbingIndex ) {}
    
    Index getProbingChannels(MessageTag outletId) const {
        RNBO_UNUSED(outletId);
        return 0;
    }
    
    Index getIsMuted()  {
        return this->isMuted;
    }
    
    void setIsMuted(Index v)  {
        this->isMuted = v;
    }
    
    Index getPatcherSerial() const {
        return 0;
    }
    
    void getState(PatcherStateInterface& ) {}
    
    void setState() {}
    
    void getPreset(PatcherStateInterface& ) {}
    
    void processTempoEvent(MillisecondTime , Tempo ) {}
    
    void processTransportEvent(MillisecondTime , TransportState ) {}
    
    void processBeatTimeEvent(MillisecondTime , BeatTime ) {}
    
    void onSampleRateChanged(double ) {}
    
    void processTimeSignatureEvent(MillisecondTime , int , int ) {}
    
    void setParameterValue(ParameterIndex , ParameterValue , MillisecondTime ) {}
    
    void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
        this->setParameterValue(index, value, time);
    }
    
    void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
        this->setParameterValueNormalized(index, value, time);
    }
    
    ParameterValue getParameterValue(ParameterIndex index)  {
        switch (index) {
        default:
            {
            return 0;
            }
        }
    }
    
    ParameterIndex getNumSignalInParameters() const {
        return 0;
    }
    
    ParameterIndex getNumSignalOutParameters() const {
        return 0;
    }
    
    ParameterIndex getNumParameters() const {
        return 0;
    }
    
    ConstCharPointer getParameterName(ParameterIndex index) const {
        switch (index) {
        default:
            {
            return "bogus";
            }
        }
    }
    
    ConstCharPointer getParameterId(ParameterIndex index) const {
        switch (index) {
        default:
            {
            return "bogus";
            }
        }
    }
    
    void getParameterInfo(ParameterIndex , ParameterInfo * ) const {}
    
    void sendParameter(ParameterIndex index, bool ignoreValue) {
        this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
    }
    
    void setParameterOffset(ParameterIndex offset) {
        this->parameterOffset = offset;
    }
    
    ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
        if (steps == 1) {
            if (normalizedValue > 0) {
                normalizedValue = 1.;
            }
        } else {
            ParameterValue oneStep = (number)1. / (steps - 1);
            ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
            normalizedValue = numberOfSteps * oneStep;
        }
    
        return normalizedValue;
    }
    
    ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
        switch (index) {
        default:
            {
            return value;
            }
        }
    }
    
    ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
        value = (value < 0 ? 0 : (value > 1 ? 1 : value));
    
        switch (index) {
        default:
            {
            return value;
            }
        }
    }
    
    ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
        switch (index) {
        default:
            {
            return value;
            }
        }
    }
    
    void scheduleParamInit(ParameterIndex index, Index order) {
        this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
    }
    
    void processClockEvent(MillisecondTime , ClockId , bool , ParameterValue ) {}
    
    void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}
    
    void processOutletEvent(
        EngineLink* sender,
        OutletIndex index,
        ParameterValue value,
        MillisecondTime time
    ) {
        this->updateTime(time);
        this->processOutletAtCurrentTime(sender, index, value);
    }
    
    void processNumMessage(MessageTag tag, MessageTag objectId, MillisecondTime time, number payload) {
        this->updateTime(time);
    
        switch (tag) {
        case TAG("valin"):
            {
            if (TAG("filters/number_obj-45") == objectId)
                this->numberobj_01_valin_set(payload);
    
            if (TAG("filters/number_obj-40") == objectId)
                this->numberobj_02_valin_set(payload);
    
            break;
            }
        case TAG("format"):
            {
            if (TAG("filters/number_obj-45") == objectId)
                this->numberobj_01_format_set(payload);
    
            if (TAG("filters/number_obj-40") == objectId)
                this->numberobj_02_format_set(payload);
    
            break;
            }
        }
    }
    
    void processListMessage(MessageTag , MessageTag , MillisecondTime , const list& ) {}
    
    void processBangMessage(MessageTag tag, MessageTag objectId, MillisecondTime time) {
        this->updateTime(time);
    
        switch (tag) {
        case TAG("bangin"):
            {
            if (TAG("filters/button_obj-38") == objectId)
                this->button_01_bangin_bang();
    
            break;
            }
        }
    }
    
    MessageTagInfo resolveTag(MessageTag tag) const {
        switch (tag) {
        case TAG("valout"):
            {
            return "valout";
            }
        case TAG("filters/number_obj-45"):
            {
            return "filters/number_obj-45";
            }
        case TAG("setup"):
            {
            return "setup";
            }
        case TAG("filters/number_obj-40"):
            {
            return "filters/number_obj-40";
            }
        case TAG("bangout"):
            {
            return "bangout";
            }
        case TAG("filters/button_obj-38"):
            {
            return "filters/button_obj-38";
            }
        case TAG("valin"):
            {
            return "valin";
            }
        case TAG("format"):
            {
            return "format";
            }
        case TAG("bangin"):
            {
            return "bangin";
            }
        }
    
        return nullptr;
    }
    
    DataRef* getDataRef(DataRefIndex index)  {
        switch (index) {
        default:
            {
            return nullptr;
            }
        }
    }
    
    DataRefIndex getNumDataRefs() const {
        return 0;
    }
    
    void fillDataRef(DataRefIndex , DataRef& ) {}
    
    void processDataViewUpdate(DataRefIndex , MillisecondTime ) {}
    
    void initialize() {
        this->assign_defaults();
        this->setState();
    }
    
    protected:
    
    void numberobj_01_valin_set(number v) {
        this->numberobj_01_value_set(v);
    }
    
    void numberobj_01_format_set(number v) {
        this->numberobj_01_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
    }
    
    void eventinlet_01_out1_bang_bang() {
        this->numberobj_01_value_bang();
    }
    
    void eventinlet_01_out1_list_set(const list& v) {
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->numberobj_01_value_set(converted);
        }
    }
    
    void numberobj_02_valin_set(number v) {
        this->numberobj_02_value_set(v);
    }
    
    void numberobj_02_format_set(number v) {
        this->numberobj_02_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
    }
    
    void eventinlet_02_out1_bang_bang() {
        this->numberobj_02_value_bang();
    }
    
    void eventinlet_02_out1_list_set(const list& v) {
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->numberobj_02_value_set(converted);
        }
    }
    
    void button_01_bangin_bang() {
        this->button_01_bangval_bang();
    }
    
    number msToSamps(MillisecondTime ms, number sampleRate) {
        return ms * sampleRate * 0.001;
    }
    
    MillisecondTime sampsToMs(SampleIndex samps) {
        return samps * (this->invsr * 1000);
    }
    
    Index getMaxBlockSize() const {
        return this->maxvs;
    }
    
    number getSampleRate() const {
        return this->sr;
    }
    
    bool hasFixedVectorSize() const {
        return false;
    }
    
    Index getNumInputChannels() const {
        return 2;
    }
    
    Index getNumOutputChannels() const {
        return 2;
    }
    
    void initializeObjects() {
        this->numberobj_01_init();
        this->numberobj_02_init();
    }
    
    void sendOutlet(OutletIndex index, ParameterValue value) {
        this->getEngine()->sendOutlet(this, index, value);
    }
    
    void startup() {}
    
    void allocateDataRefs() {}
    
    void lores_02_cutoff_set(number v) {
        this->lores_02_cutoff = v;
    }
    
    void lores_01_cutoff_set(number v) {
        this->lores_01_cutoff = v;
    }
    
    void numberobj_01_output_set(number v) {
        this->lores_02_cutoff_set(v);
        this->lores_01_cutoff_set(v);
    }
    
    void numberobj_01_value_set(number v) {
        this->numberobj_01_value_setter(v);
        v = this->numberobj_01_value;
        number localvalue = v;
    
        if (this->numberobj_01_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(
            TAG("valout"),
            TAG("filters/number_obj-45"),
            localvalue,
            this->_currentTime
        );
    
        this->numberobj_01_output_set(localvalue);
    }
    
    void eventinlet_01_out1_number_set(number v) {
        this->numberobj_01_value_set(v);
    }
    
    void lores_02_resonance_set(number v) {
        this->lores_02_resonance_setter(v);
        v = this->lores_02_resonance;
    }
    
    void lores_01_resonance_set(number v) {
        this->lores_01_resonance_setter(v);
        v = this->lores_01_resonance;
    }
    
    void numberobj_02_output_set(number v) {
        this->lores_02_resonance_set(v);
        this->lores_01_resonance_set(v);
    }
    
    void numberobj_02_value_set(number v) {
        this->numberobj_02_value_setter(v);
        v = this->numberobj_02_value;
        number localvalue = v;
    
        if (this->numberobj_02_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(
            TAG("valout"),
            TAG("filters/number_obj-40"),
            localvalue,
            this->_currentTime
        );
    
        this->numberobj_02_output_set(localvalue);
    }
    
    void eventinlet_02_out1_number_set(number v) {
        this->numberobj_02_value_set(v);
    }
    
    void numberobj_01_value_bang() {
        number v = this->numberobj_01_value;
        number localvalue = v;
    
        if (this->numberobj_01_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(
            TAG("valout"),
            TAG("filters/number_obj-45"),
            localvalue,
            this->_currentTime
        );
    
        this->numberobj_01_output_set(localvalue);
    }
    
    void numberobj_02_value_bang() {
        number v = this->numberobj_02_value;
        number localvalue = v;
    
        if (this->numberobj_02_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(
            TAG("valout"),
            TAG("filters/number_obj-40"),
            localvalue,
            this->_currentTime
        );
    
        this->numberobj_02_output_set(localvalue);
    }
    
    void lores_01_clear_bang() {
        this->lores_01_reset();
    }
    
    void lores_02_clear_bang() {
        this->lores_02_reset();
    }
    
    void button_01_output_bang() {
        this->lores_01_clear_bang();
        this->lores_02_clear_bang();
    }
    
    void button_01_bangval_bang() {
        this->getEngine()->sendBangMessage(TAG("bangout"), TAG("filters/button_obj-38"), this->_currentTime);;
        this->button_01_output_bang();
    }
    
    void lores_01_perform(
        number cutoff,
        number resonance,
        const SampleValue * input,
        SampleValue * out,
        Index n
    ) {
        auto __lores_01_y_2 = this->lores_01_y_2;
        auto __lores_01_y_1 = this->lores_01_y_1;
        auto __lores_01_x_0 = this->lores_01_x_0;
        auto __lores_01_b_0 = this->lores_01_b_0;
        auto __lores_01_a_1 = this->lores_01_a_1;
        auto __lores_01_a_2 = this->lores_01_a_2;
        auto __lores_01_last_freq_calc = this->lores_01_last_freq_calc;
        auto __lores_01_last_res_calc = this->lores_01_last_res_calc;
        auto __lores_01_last_frequency = this->lores_01_last_frequency;
        auto __lores_01_last_resonance = this->lores_01_last_resonance;
    
        for (Index i = 0; i < n; i++) {
            if (resonance != __lores_01_last_resonance || cutoff != __lores_01_last_frequency) {
                __lores_01_last_res_calc = rnbo_exp(resonance * 0.125) * 0.882497;
                __lores_01_last_freq_calc = rnbo_cos(2.0 * pi01() / this->sr * cutoff);
                __lores_01_last_resonance = resonance;
                __lores_01_last_frequency = cutoff;
            }
    
            number res_temp = __lores_01_last_res_calc;
            number freq_temp = __lores_01_last_freq_calc;
            __lores_01_a_2 = res_temp * res_temp;
            __lores_01_a_1 = -2.0 * res_temp * freq_temp;
            __lores_01_b_0 = 1.0 + __lores_01_a_1 + __lores_01_a_2;
            __lores_01_x_0 = input[(Index)i];
            number y_0 = __lores_01_x_0 * __lores_01_b_0 - __lores_01_y_1 * __lores_01_a_1 - __lores_01_y_2 * __lores_01_a_2;
            __lores_01_y_2 = __lores_01_y_1;
            __lores_01_y_1 = y_0;
            out[(Index)i] = y_0;
        }
    
        this->lores_01_last_resonance = __lores_01_last_resonance;
        this->lores_01_last_frequency = __lores_01_last_frequency;
        this->lores_01_last_res_calc = __lores_01_last_res_calc;
        this->lores_01_last_freq_calc = __lores_01_last_freq_calc;
        this->lores_01_a_2 = __lores_01_a_2;
        this->lores_01_a_1 = __lores_01_a_1;
        this->lores_01_b_0 = __lores_01_b_0;
        this->lores_01_x_0 = __lores_01_x_0;
        this->lores_01_y_1 = __lores_01_y_1;
        this->lores_01_y_2 = __lores_01_y_2;
    }
    
    void lores_02_perform(
        number cutoff,
        number resonance,
        const SampleValue * input,
        SampleValue * out,
        Index n
    ) {
        auto __lores_02_y_2 = this->lores_02_y_2;
        auto __lores_02_y_1 = this->lores_02_y_1;
        auto __lores_02_x_0 = this->lores_02_x_0;
        auto __lores_02_b_0 = this->lores_02_b_0;
        auto __lores_02_a_1 = this->lores_02_a_1;
        auto __lores_02_a_2 = this->lores_02_a_2;
        auto __lores_02_last_freq_calc = this->lores_02_last_freq_calc;
        auto __lores_02_last_res_calc = this->lores_02_last_res_calc;
        auto __lores_02_last_frequency = this->lores_02_last_frequency;
        auto __lores_02_last_resonance = this->lores_02_last_resonance;
    
        for (Index i = 0; i < n; i++) {
            if (resonance != __lores_02_last_resonance || cutoff != __lores_02_last_frequency) {
                __lores_02_last_res_calc = rnbo_exp(resonance * 0.125) * 0.882497;
                __lores_02_last_freq_calc = rnbo_cos(2.0 * pi01() / this->sr * cutoff);
                __lores_02_last_resonance = resonance;
                __lores_02_last_frequency = cutoff;
            }
    
            number res_temp = __lores_02_last_res_calc;
            number freq_temp = __lores_02_last_freq_calc;
            __lores_02_a_2 = res_temp * res_temp;
            __lores_02_a_1 = -2.0 * res_temp * freq_temp;
            __lores_02_b_0 = 1.0 + __lores_02_a_1 + __lores_02_a_2;
            __lores_02_x_0 = input[(Index)i];
            number y_0 = __lores_02_x_0 * __lores_02_b_0 - __lores_02_y_1 * __lores_02_a_1 - __lores_02_y_2 * __lores_02_a_2;
            __lores_02_y_2 = __lores_02_y_1;
            __lores_02_y_1 = y_0;
            out[(Index)i] = y_0;
        }
    
        this->lores_02_last_resonance = __lores_02_last_resonance;
        this->lores_02_last_frequency = __lores_02_last_frequency;
        this->lores_02_last_res_calc = __lores_02_last_res_calc;
        this->lores_02_last_freq_calc = __lores_02_last_freq_calc;
        this->lores_02_a_2 = __lores_02_a_2;
        this->lores_02_a_1 = __lores_02_a_1;
        this->lores_02_b_0 = __lores_02_b_0;
        this->lores_02_x_0 = __lores_02_x_0;
        this->lores_02_y_1 = __lores_02_y_1;
        this->lores_02_y_2 = __lores_02_y_2;
    }
    
    void stackprotect_perform(Index n) {
        RNBO_UNUSED(n);
        auto __stackprotect_count = this->stackprotect_count;
        __stackprotect_count = 0;
        this->stackprotect_count = __stackprotect_count;
    }
    
    void lores_01_resonance_setter(number v) {
        if (v < 0.0) {
            v = 0.0;
        } else if (v >= 1.0) {
            v = 1.0 - 1E-20;
        }
    
        this->lores_01_resonance = v;
    }
    
    void lores_02_resonance_setter(number v) {
        if (v < 0.0) {
            v = 0.0;
        } else if (v >= 1.0) {
            v = 1.0 - 1E-20;
        }
    
        this->lores_02_resonance = v;
    }
    
    void numberobj_01_value_setter(number v) {
        number localvalue = v;
    
        if (this->numberobj_01_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->numberobj_01_value = localvalue;
    }
    
    void numberobj_02_value_setter(number v) {
        number localvalue = v;
    
        if (this->numberobj_02_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->numberobj_02_value = localvalue;
    }
    
    void lores_01_reset() {
        this->lores_01_y_1 = 0;
        this->lores_01_y_2 = 0;
        this->lores_01_last_resonance = 0;
        this->lores_01_last_frequency = 0;
        this->lores_01_last_res_calc = 0;
        this->lores_01_last_freq_calc = 0;
    }
    
    void lores_01_dspsetup(bool force) {
        if ((bool)(this->lores_01_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->lores_01_reset();
        this->lores_01_setupDone = true;
    }
    
    void lores_02_reset() {
        this->lores_02_y_1 = 0;
        this->lores_02_y_2 = 0;
        this->lores_02_last_resonance = 0;
        this->lores_02_last_frequency = 0;
        this->lores_02_last_res_calc = 0;
        this->lores_02_last_freq_calc = 0;
    }
    
    void lores_02_dspsetup(bool force) {
        if ((bool)(this->lores_02_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->lores_02_reset();
        this->lores_02_setupDone = true;
    }
    
    void numberobj_01_init() {
        this->numberobj_01_currentFormat = 6;
        this->getEngine()->sendNumMessage(TAG("setup"), TAG("filters/number_obj-45"), 1, this->_currentTime);
    }
    
    void numberobj_01_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->numberobj_01_value;
    }
    
    void numberobj_01_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->numberobj_01_value_set(preset["value"]);
    }
    
    void numberobj_02_init() {
        this->numberobj_02_currentFormat = 6;
        this->getEngine()->sendNumMessage(TAG("setup"), TAG("filters/number_obj-40"), 1, this->_currentTime);
    }
    
    void numberobj_02_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->numberobj_02_value;
    }
    
    void numberobj_02_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->numberobj_02_value_set(preset["value"]);
    }
    
    bool stackprotect_check() {
        this->stackprotect_count++;
    
        if (this->stackprotect_count > 128) {
            console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
            return true;
        }
    
        return false;
    }
    
    void updateTime(MillisecondTime time) {
        this->_currentTime = time;
        this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));
    
        if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
            this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;
    
        if (this->sampleOffsetIntoNextAudioBuffer < 0)
            this->sampleOffsetIntoNextAudioBuffer = 0;
    }
    
    void assign_defaults()
    {
        lores_01_cutoff = 200;
        lores_01_resonance = 0.75;
        lores_01_resonance_setter(lores_01_resonance);
        lores_02_cutoff = 200;
        lores_02_resonance = 0.75;
        lores_02_resonance_setter(lores_02_resonance);
        numberobj_01_value = 0;
        numberobj_01_value_setter(numberobj_01_value);
        numberobj_02_value = 0;
        numberobj_02_value_setter(numberobj_02_value);
        _currentTime = 0;
        audioProcessSampleCount = 0;
        sampleOffsetIntoNextAudioBuffer = 0;
        zeroBuffer = nullptr;
        dummyBuffer = nullptr;
        didAllocateSignals = 0;
        vs = 0;
        maxvs = 0;
        sr = 44100;
        invsr = 0.00002267573696;
        lores_01_setupDone = false;
        lores_02_setupDone = false;
        numberobj_01_currentFormat = 6;
        numberobj_01_lastValue = 0;
        numberobj_02_currentFormat = 6;
        numberobj_02_lastValue = 0;
        stackprotect_count = 0;
        _voiceIndex = 0;
        _noteNumber = 0;
        isMuted = 1;
        parameterOffset = 0;
    }
    
    // member variables
    
        number lores_01_cutoff;
        number lores_01_resonance;
        number lores_02_cutoff;
        number lores_02_resonance;
        number numberobj_01_value;
        number numberobj_02_value;
        MillisecondTime _currentTime;
        SampleIndex audioProcessSampleCount;
        SampleIndex sampleOffsetIntoNextAudioBuffer;
        signal zeroBuffer;
        signal dummyBuffer;
        bool didAllocateSignals;
        Index vs;
        Index maxvs;
        number sr;
        number invsr;
        number lores_01_b_0;
        number lores_01_a_1;
        number lores_01_a_2;
        number lores_01_x_0;
        number lores_01_y_1;
        number lores_01_y_2;
        number lores_01_last_resonance;
        number lores_01_last_frequency;
        number lores_01_last_res_calc;
        number lores_01_last_freq_calc;
        bool lores_01_setupDone;
        number lores_02_b_0;
        number lores_02_a_1;
        number lores_02_a_2;
        number lores_02_x_0;
        number lores_02_y_1;
        number lores_02_y_2;
        number lores_02_last_resonance;
        number lores_02_last_frequency;
        number lores_02_last_res_calc;
        number lores_02_last_freq_calc;
        bool lores_02_setupDone;
        Int numberobj_01_currentFormat;
        number numberobj_01_lastValue;
        Int numberobj_02_currentFormat;
        number numberobj_02_lastValue;
        number stackprotect_count;
        Index _voiceIndex;
        Int _noteNumber;
        Index isMuted;
        ParameterIndex parameterOffset;
    
};

rnbomatic()
{
}

~rnbomatic()
{
    delete this->p_01;
}

rnbomatic* getTopLevelPatcher() {
    return this;
}

void cancelClockEvents()
{
    getEngine()->flushClockEvents(this, -871642103, false);
}

template <typename T> void listquicksort(T& arr, T& sortindices, Int l, Int h, bool ascending) {
    if (l < h) {
        Int p = (Int)(this->listpartition(arr, sortindices, l, h, ascending));
        this->listquicksort(arr, sortindices, l, p - 1, ascending);
        this->listquicksort(arr, sortindices, p + 1, h, ascending);
    }
}

template <typename T> Int listpartition(T& arr, T& sortindices, Int l, Int h, bool ascending) {
    number x = arr[(Index)h];
    Int i = (Int)(l - 1);

    for (Int j = (Int)(l); j <= h - 1; j++) {
        bool asc = (bool)((bool)(ascending) && arr[(Index)j] <= x);
        bool desc = (bool)((bool)(!(bool)(ascending)) && arr[(Index)j] >= x);

        if ((bool)(asc) || (bool)(desc)) {
            i++;
            this->listswapelements(arr, i, j);
            this->listswapelements(sortindices, i, j);
        }
    }

    i++;
    this->listswapelements(arr, i, h);
    this->listswapelements(sortindices, i, h);
    return i;
}

template <typename T> void listswapelements(T& arr, Int a, Int b) {
    auto tmp = arr[(Index)a];
    arr[(Index)a] = arr[(Index)b];
    arr[(Index)b] = tmp;
}

inline number safediv(number num, number denom) {
    return (denom == 0.0 ? 0.0 : num / denom);
}

number maximum(number x, number y) {
    return (x < y ? y : x);
}

number samplerate() {
    return this->sr;
}

number mstosamps(MillisecondTime ms) {
    return ms * this->sr * 0.001;
}

Index vectorsize() {
    return this->vs;
}

number minimum(number x, number y) {
    return (y < x ? y : x);
}

MillisecondTime currenttime() {
    return this->_currentTime;
}

number tempo() {
    return this->getTopLevelPatcher()->globaltransport_getTempo(this->currenttime());
}

number mstobeats(number ms) {
    return ms * this->tempo() * 0.008 / (number)480;
}

MillisecondTime sampstoms(number samps) {
    return samps * 1000 / this->sr;
}

Index getNumMidiInputPorts() const {
    return 1;
}

void processMidiEvent(MillisecondTime time, int port, ConstByteArray data, Index length) {
    this->updateTime(time);
    this->midiin_01_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
}

Index getNumMidiOutputPorts() const {
    return 1;
}

void process(
    const SampleValue * const* inputs,
    Index numInputs,
    SampleValue * const* outputs,
    Index numOutputs,
    Index n
) {
    this->vs = n;
    this->updateTime(this->getEngine()->getCurrentTime());
    SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
    SampleValue * out2 = (numOutputs >= 2 && outputs[1] ? outputs[1] : this->dummyBuffer);
    const SampleValue * in1 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
    const SampleValue * in2 = (numInputs >= 2 && inputs[1] ? inputs[1] : this->zeroBuffer);

    this->slide_tilde_01_perform(
        this->slide_tilde_01_x,
        this->slide_tilde_01_up,
        this->slide_tilde_01_down,
        this->signals[0],
        n
    );

    this->cycle_tilde_01_perform(
        this->signals[0],
        this->cycle_tilde_01_phase_offset,
        this->signals[1],
        this->dummyBuffer,
        n
    );

    this->slide_tilde_02_perform(
        this->slide_tilde_02_x,
        this->slide_tilde_02_up,
        this->slide_tilde_02_down,
        this->signals[0],
        n
    );

    this->cycle_tilde_02_perform(
        this->signals[0],
        this->cycle_tilde_02_phase_offset,
        this->signals[2],
        this->dummyBuffer,
        n
    );

    this->slide_tilde_03_perform(
        this->slide_tilde_03_x,
        this->slide_tilde_03_up,
        this->slide_tilde_03_down,
        this->signals[0],
        n
    );

    this->dspexpr_01_perform(this->signals[1], this->signals[0], this->signals[3], n);

    this->slide_tilde_04_perform(
        this->slide_tilde_04_x,
        this->slide_tilde_04_up,
        this->slide_tilde_04_down,
        this->signals[0],
        n
    );

    this->dspexpr_03_perform(this->signals[2], this->signals[0], this->signals[1], n);
    this->dspexpr_02_perform(this->signals[3], this->signals[1], this->signals[0], n);

    this->groove_01_perform(
        this->groove_01_rate_auto,
        this->groove_01_begin,
        this->groove_01_end,
        this->signals[1],
        this->dummyBuffer,
        n
    );

    this->p_01_perform(in1, in2, this->signals[3], this->signals[2], n);
    this->signaladder_01_perform(this->signals[3], this->signals[0], this->signals[1], out1, n);
    this->signaladder_02_perform(this->signals[2], this->signals[0], this->signals[1], out2, n);

    this->lores_03_perform(
        this->lores_03_cutoff,
        this->lores_03_resonance,
        this->zeroBuffer,
        this->dummyBuffer,
        n
    );

    this->stackprotect_perform(n);
    this->globaltransport_advance();
    this->audioProcessSampleCount += this->vs;
}

void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
    if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
        Index i;

        for (i = 0; i < 4; i++) {
            this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
        }

        this->globaltransport_tempo = resizeSignal(this->globaltransport_tempo, this->maxvs, maxBlockSize);
        this->globaltransport_state = resizeSignal(this->globaltransport_state, this->maxvs, maxBlockSize);
        this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
        this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
        this->didAllocateSignals = true;
    }

    const bool sampleRateChanged = sampleRate != this->sr;
    const bool maxvsChanged = maxBlockSize != this->maxvs;
    const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;

    if (sampleRateChanged || maxvsChanged) {
        this->vs = maxBlockSize;
        this->maxvs = maxBlockSize;
        this->sr = sampleRate;
        this->invsr = 1 / sampleRate;
    }

    this->cycle_tilde_01_dspsetup(forceDSPSetup);
    this->cycle_tilde_02_dspsetup(forceDSPSetup);
    this->data_01_dspsetup(forceDSPSetup);
    this->groove_01_dspsetup(forceDSPSetup);
    this->lores_03_dspsetup(forceDSPSetup);
    this->globaltransport_dspsetup(forceDSPSetup);
    this->p_01->prepareToProcess(sampleRate, maxBlockSize, force);

    if (sampleRateChanged)
        this->onSampleRateChanged(sampleRate);
}

void setProbingTarget(MessageTag id) {
    switch (id) {
    default:
        {
        this->setProbingIndex(-1);
        break;
        }
    }
}

void setProbingIndex(ProbingIndex ) {}

Index getProbingChannels(MessageTag outletId) const {
    RNBO_UNUSED(outletId);
    return 0;
}

DataRef* getDataRef(DataRefIndex index)  {
    switch (index) {
    case 0:
        {
        return addressOf(this->RNBODefaultSinus);
        break;
        }
    case 1:
        {
        return addressOf(this->rnbuff1);
        break;
        }
    default:
        {
        return nullptr;
        }
    }
}

DataRefIndex getNumDataRefs() const {
    return 2;
}

void fillRNBODefaultSinus(DataRef& ref) {
    Float64BufferRef buffer;
    buffer = new Float64Buffer(ref);
    number bufsize = buffer->getSize();

    for (Index i = 0; i < bufsize; i++) {
        buffer[i] = rnbo_cos(i * 3.14159265358979323846 * 2. / bufsize);
    }
}

void fillDataRef(DataRefIndex index, DataRef& ref) {
    switch (index) {
    case 0:
        {
        this->fillRNBODefaultSinus(ref);
        break;
        }
    }
}

void zeroDataRef(DataRef& ref) {
    ref->setZero();
}

void processDataViewUpdate(DataRefIndex index, MillisecondTime time) {
    this->updateTime(time);

    if (index == 0) {
        this->cycle_tilde_01_buffer = new Float64Buffer(this->RNBODefaultSinus);
        this->cycle_tilde_01_bufferUpdated();
        this->cycle_tilde_02_buffer = new Float64Buffer(this->RNBODefaultSinus);
        this->cycle_tilde_02_bufferUpdated();
    }

    if (index == 1) {
        this->data_01_buffer = new Float32Buffer(this->rnbuff1);
        this->data_01_bufferUpdated();
        this->groove_01_buffer = new Float32Buffer(this->rnbuff1);
    }

    this->p_01->processDataViewUpdate(index, time);
}

void initialize() {
    this->RNBODefaultSinus = initDataRef("RNBODefaultSinus", true, nullptr, "buffer~");
    this->rnbuff1 = initDataRef("rnbuff1", false, "cherokee.aif", "buffer~");
    this->assign_defaults();
    this->setState();
    this->RNBODefaultSinus->setIndex(0);
    this->cycle_tilde_01_buffer = new Float64Buffer(this->RNBODefaultSinus);
    this->cycle_tilde_02_buffer = new Float64Buffer(this->RNBODefaultSinus);
    this->rnbuff1->setIndex(1);
    this->data_01_buffer = new Float32Buffer(this->rnbuff1);
    this->groove_01_buffer = new Float32Buffer(this->rnbuff1);
    this->initializeObjects();
    this->allocateDataRefs();
    this->startup();
}

Index getIsMuted()  {
    return this->isMuted;
}

void setIsMuted(Index v)  {
    this->isMuted = v;
}

Index getPatcherSerial() const {
    return 0;
}

void getState(PatcherStateInterface& ) {}

void setState() {
    this->p_01 = new RNBOSubpatcher_84();
    this->p_01->setEngineAndPatcher(this->getEngine(), this);
    this->p_01->initialize();
    this->p_01->setParameterOffset(this->getParameterOffset(this->p_01));
}

void getPreset(PatcherStateInterface& preset) {
    preset["__presetid"] = "rnbo";
    this->param_01_getPresetValue(getSubState(preset, "freq1"));
    this->param_02_getPresetValue(getSubState(preset, "freq2"));
    this->param_03_getPresetValue(getSubState(preset, "vol1"));
    this->param_04_getPresetValue(getSubState(preset, "vol2"));
    this->param_05_getPresetValue(getSubState(preset, "play"));
    this->param_06_getPresetValue(getSubState(preset, "cutoff"));
    this->param_07_getPresetValue(getSubState(preset, "resonance"));
    this->p_01->getPreset(getSubState(getSubState(preset, "__sps"), "filters"));
}

void setPreset(MillisecondTime time, PatcherStateInterface& preset) {
    this->updateTime(time);
    this->param_01_setPresetValue(getSubState(preset, "freq1"));
    this->param_02_setPresetValue(getSubState(preset, "freq2"));
    this->param_03_setPresetValue(getSubState(preset, "vol1"));
    this->param_04_setPresetValue(getSubState(preset, "vol2"));
    this->param_05_setPresetValue(getSubState(preset, "play"));
    this->param_06_setPresetValue(getSubState(preset, "cutoff"));
    this->param_07_setPresetValue(getSubState(preset, "resonance"));
}

void processTempoEvent(MillisecondTime time, Tempo tempo) {
    this->updateTime(time);

    if (this->globaltransport_setTempo(this->_currentTime, tempo, false)) {
        this->p_01->processTempoEvent(time, tempo);
    }
}

void processTransportEvent(MillisecondTime time, TransportState state) {
    this->updateTime(time);

    if (this->globaltransport_setState(this->_currentTime, state, false)) {
        this->p_01->processTransportEvent(time, state);
    }
}

void processBeatTimeEvent(MillisecondTime time, BeatTime beattime) {
    this->updateTime(time);

    if (this->globaltransport_setBeatTime(this->_currentTime, beattime, false)) {
        this->p_01->processBeatTimeEvent(time, beattime);
    }
}

void onSampleRateChanged(double ) {}

void processTimeSignatureEvent(MillisecondTime time, int numerator, int denominator) {
    this->updateTime(time);

    if (this->globaltransport_setTimeSignature(this->_currentTime, numerator, denominator, false)) {
        this->p_01->processTimeSignatureEvent(time, numerator, denominator);
    }
}

void setParameterValue(ParameterIndex index, ParameterValue v, MillisecondTime time) {
    this->updateTime(time);

    switch (index) {
    case 0:
        {
        this->param_01_value_set(v);
        break;
        }
    case 1:
        {
        this->param_02_value_set(v);
        break;
        }
    case 2:
        {
        this->param_03_value_set(v);
        break;
        }
    case 3:
        {
        this->param_04_value_set(v);
        break;
        }
    case 4:
        {
        this->param_05_value_set(v);
        break;
        }
    case 5:
        {
        this->param_06_value_set(v);
        break;
        }
    case 6:
        {
        this->param_07_value_set(v);
        break;
        }
    default:
        {
        index -= 7;

        if (index < this->p_01->getNumParameters())
            this->p_01->setParameterValue(index, v, time);

        break;
        }
    }
}

void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
    this->setParameterValue(index, value, time);
}

void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
    this->setParameterValueNormalized(index, value, time);
}

ParameterValue getParameterValue(ParameterIndex index)  {
    switch (index) {
    case 0:
        {
        return this->param_01_value;
        }
    case 1:
        {
        return this->param_02_value;
        }
    case 2:
        {
        return this->param_03_value;
        }
    case 3:
        {
        return this->param_04_value;
        }
    case 4:
        {
        return this->param_05_value;
        }
    case 5:
        {
        return this->param_06_value;
        }
    case 6:
        {
        return this->param_07_value;
        }
    default:
        {
        index -= 7;

        if (index < this->p_01->getNumParameters())
            return this->p_01->getParameterValue(index);

        return 0;
        }
    }
}

ParameterIndex getNumSignalInParameters() const {
    return 0;
}

ParameterIndex getNumSignalOutParameters() const {
    return 0;
}

ParameterIndex getNumParameters() const {
    return 7 + this->p_01->getNumParameters();
}

ConstCharPointer getParameterName(ParameterIndex index) const {
    switch (index) {
    case 0:
        {
        return "freq1";
        }
    case 1:
        {
        return "freq2";
        }
    case 2:
        {
        return "vol1";
        }
    case 3:
        {
        return "vol2";
        }
    case 4:
        {
        return "play";
        }
    case 5:
        {
        return "cutoff";
        }
    case 6:
        {
        return "resonance";
        }
    default:
        {
        index -= 7;

        if (index < this->p_01->getNumParameters())
            return this->p_01->getParameterName(index);

        return "bogus";
        }
    }
}

ConstCharPointer getParameterId(ParameterIndex index) const {
    switch (index) {
    case 0:
        {
        return "freq1";
        }
    case 1:
        {
        return "freq2";
        }
    case 2:
        {
        return "vol1";
        }
    case 3:
        {
        return "vol2";
        }
    case 4:
        {
        return "play";
        }
    case 5:
        {
        return "cutoff";
        }
    case 6:
        {
        return "resonance";
        }
    default:
        {
        index -= 7;

        if (index < this->p_01->getNumParameters())
            return this->p_01->getParameterId(index);

        return "bogus";
        }
    }
}

void getParameterInfo(ParameterIndex index, ParameterInfo * info) const {
    {
        switch (index) {
        case 0:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 220;
            info->max = 440;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Frequency 1";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 1:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 220;
            info->max = 440;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Frequency 2";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 2:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 0;
            info->max = 0.5;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Volume 1";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 3:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 0;
            info->max = 0.5;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Volume 2";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 4:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1;
            info->min = 0.5;
            info->max = 2;
            info->exponent = 2;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Play";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 5:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 0;
            info->max = 2000;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Cutoff";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 6:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0.5;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Resonance";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        default:
            {
            index -= 7;

            if (index < this->p_01->getNumParameters())
                this->p_01->getParameterInfo(index, info);

            break;
            }
        }
    }
}

void sendParameter(ParameterIndex index, bool ignoreValue) {
    this->getEngine()->notifyParameterValueChanged(index, (ignoreValue ? 0 : this->getParameterValue(index)), ignoreValue);
}

ParameterIndex getParameterOffset(BaseInterface* subpatcher) const {
    if (subpatcher == this->p_01)
        return 7;

    return 0;
}

ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
    if (steps == 1) {
        if (normalizedValue > 0) {
            normalizedValue = 1.;
        }
    } else {
        ParameterValue oneStep = (number)1. / (steps - 1);
        ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
        normalizedValue = numberOfSteps * oneStep;
    }

    return normalizedValue;
}

ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
    switch (index) {
    case 6:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            ParameterValue normalizedValue = (value - 0) / (1 - 0);
            return normalizedValue;
        }
        }
    case 5:
        {
        {
            value = (value < 0 ? 0 : (value > 2000 ? 2000 : value));
            ParameterValue normalizedValue = (value - 0) / (2000 - 0);
            return normalizedValue;
        }
        }
    case 2:
    case 3:
        {
        {
            value = (value < 0 ? 0 : (value > 0.5 ? 0.5 : value));
            ParameterValue normalizedValue = (value - 0) / (0.5 - 0);
            return normalizedValue;
        }
        }
    case 0:
    case 1:
        {
        {
            value = (value < 220 ? 220 : (value > 440 ? 440 : value));
            ParameterValue normalizedValue = (value - 220) / (440 - 220);
            return normalizedValue;
        }
        }
    case 4:
        {
        {
            value = (value < 0.5 ? 0.5 : (value > 2 ? 2 : value));
            ParameterValue normalizedValue = (value - 0.5) / (2 - 0.5);

            {
                normalizedValue = rnbo_exp(rnbo_log(normalizedValue) * 1. / (number)2);
            }

            return normalizedValue;
        }
        }
    default:
        {
        index -= 7;

        if (index < this->p_01->getNumParameters())
            return this->p_01->convertToNormalizedParameterValue(index, value);

        return value;
        }
    }
}

ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
    value = (value < 0 ? 0 : (value > 1 ? 1 : value));

    switch (index) {
    case 6:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));

            {
                return 0 + value * (1 - 0);
            }
        }
        }
    case 5:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));

            {
                return 0 + value * (2000 - 0);
            }
        }
        }
    case 2:
    case 3:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));

            {
                return 0 + value * (0.5 - 0);
            }
        }
        }
    case 0:
    case 1:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));

            {
                return 220 + value * (440 - 220);
            }
        }
        }
    case 4:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));

            {
                return 0.5 + rnbo_exp(rnbo_log(value) * 2) * (2 - 0.5);
            }
        }
        }
    default:
        {
        index -= 7;

        if (index < this->p_01->getNumParameters())
            return this->p_01->convertFromNormalizedParameterValue(index, value);

        return value;
        }
    }
}

ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
    switch (index) {
    case 0:
        {
        return this->param_01_value_constrain(value);
        }
    case 1:
        {
        return this->param_02_value_constrain(value);
        }
    case 2:
        {
        return this->param_03_value_constrain(value);
        }
    case 3:
        {
        return this->param_04_value_constrain(value);
        }
    case 4:
        {
        return this->param_05_value_constrain(value);
        }
    case 5:
        {
        return this->param_06_value_constrain(value);
        }
    case 6:
        {
        return this->param_07_value_constrain(value);
        }
    default:
        {
        index -= 7;

        if (index < this->p_01->getNumParameters())
            return this->p_01->constrainParameterValue(index, value);

        return value;
        }
    }
}

void scheduleParamInit(ParameterIndex index, Index order) {
    this->paramInitIndices->push(index);
    this->paramInitOrder->push(order);
}

void processParamInitEvents() {
    this->listquicksort(
        this->paramInitOrder,
        this->paramInitIndices,
        0,
        (int)(this->paramInitOrder->length - 1),
        true
    );

    for (Index i = 0; i < this->paramInitOrder->length; i++) {
        this->getEngine()->scheduleParameterChange(
            this->paramInitIndices[i],
            this->getParameterValue(this->paramInitIndices[i]),
            0
        );
    }
}

void processClockEvent(MillisecondTime time, ClockId index, bool hasValue, ParameterValue value) {
    RNBO_UNUSED(value);
    RNBO_UNUSED(hasValue);
    this->updateTime(time);

    switch (index) {
    case -871642103:
        {
        this->loadbang_01_startupbang_bang();
        break;
        }
    }
}

void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}

void processOutletEvent(
    EngineLink* sender,
    OutletIndex index,
    ParameterValue value,
    MillisecondTime time
) {
    this->updateTime(time);
    this->processOutletAtCurrentTime(sender, index, value);
}

void processNumMessage(MessageTag tag, MessageTag objectId, MillisecondTime time, number payload) {
    this->updateTime(time);

    switch (tag) {
    case TAG("foo"):
        {
        this->inport_01_value_number_set(payload);
        break;
        }
    case TAG("listin"):
        {
        if (TAG("message_obj-63") == objectId)
            this->message_01_listin_number_set(payload);

        break;
        }
    }

    this->p_01->processNumMessage(tag, objectId, time, payload);
}

void processListMessage(
    MessageTag tag,
    MessageTag objectId,
    MillisecondTime time,
    const list& payload
) {
    this->updateTime(time);

    switch (tag) {
    case TAG("foo"):
        {
        this->inport_01_value_list_set(payload);
        break;
        }
    case TAG("listin"):
        {
        if (TAG("message_obj-63") == objectId)
            this->message_01_listin_list_set(payload);

        break;
        }
    }

    this->p_01->processListMessage(tag, objectId, time, payload);
}

void processBangMessage(MessageTag tag, MessageTag objectId, MillisecondTime time) {
    this->updateTime(time);

    switch (tag) {
    case TAG("foo"):
        {
        this->inport_01_value_bang_bang();
        break;
        }
    case TAG("listin"):
        {
        if (TAG("message_obj-63") == objectId)
            this->message_01_listin_bang_bang();

        break;
        }
    case TAG("startupbang"):
        {
        if (TAG("loadbang_obj-59") == objectId)
            this->loadbang_01_startupbang_bang();

        break;
        }
    }

    this->p_01->processBangMessage(tag, objectId, time);
}

MessageTagInfo resolveTag(MessageTag tag) const {
    switch (tag) {
    case TAG("listout"):
        {
        return "listout";
        }
    case TAG("message_obj-63"):
        {
        return "message_obj-63";
        }
    case TAG("bar"):
        {
        return "bar";
        }
    case TAG(""):
        {
        return "";
        }
    case TAG("foo"):
        {
        return "foo";
        }
    case TAG("listin"):
        {
        return "listin";
        }
    case TAG("startupbang"):
        {
        return "startupbang";
        }
    case TAG("loadbang_obj-59"):
        {
        return "loadbang_obj-59";
        }
    }

    auto subpatchResult_0 = this->p_01->resolveTag(tag);

    if (subpatchResult_0)
        return subpatchResult_0;

    return "";
}

MessageIndex getNumMessages() const {
    return 2;
}

const MessageInfo& getMessageInfo(MessageIndex index) const {
    switch (index) {
    case 0:
        {
        static const MessageInfo r0 = {
            "bar",
            Outport
        };

        return r0;
        }
    case 1:
        {
        static const MessageInfo r1 = {
            "foo",
            Inport
        };

        return r1;
        }
    }

    return NullMessageInfo;
}

protected:

void param_01_value_set(number v) {
    v = this->param_01_value_constrain(v);
    this->param_01_value = v;
    this->sendParameter(0, false);

    if (this->param_01_value != this->param_01_lastValue) {
        this->getEngine()->presetTouched();
        this->param_01_lastValue = this->param_01_value;
    }

    this->slide_tilde_01_x_set(v);
}

void param_02_value_set(number v) {
    v = this->param_02_value_constrain(v);
    this->param_02_value = v;
    this->sendParameter(1, false);

    if (this->param_02_value != this->param_02_lastValue) {
        this->getEngine()->presetTouched();
        this->param_02_lastValue = this->param_02_value;
    }

    this->slide_tilde_02_x_set(v);
}

void param_03_value_set(number v) {
    v = this->param_03_value_constrain(v);
    this->param_03_value = v;
    this->sendParameter(2, false);

    if (this->param_03_value != this->param_03_lastValue) {
        this->getEngine()->presetTouched();
        this->param_03_lastValue = this->param_03_value;
    }

    this->slide_tilde_03_x_set(v);
}

void param_04_value_set(number v) {
    v = this->param_04_value_constrain(v);
    this->param_04_value = v;
    this->sendParameter(3, false);

    if (this->param_04_value != this->param_04_lastValue) {
        this->getEngine()->presetTouched();
        this->param_04_lastValue = this->param_04_value;
    }

    this->slide_tilde_04_x_set(v);
}

void param_05_value_set(number v) {
    v = this->param_05_value_constrain(v);
    this->param_05_value = v;
    this->sendParameter(4, false);

    if (this->param_05_value != this->param_05_lastValue) {
        this->getEngine()->presetTouched();
        this->param_05_lastValue = this->param_05_value;
    }

    this->trigger_01_input_number_set(v);
}

void param_06_value_set(number v) {
    v = this->param_06_value_constrain(v);
    this->param_06_value = v;
    this->sendParameter(5, false);

    if (this->param_06_value != this->param_06_lastValue) {
        this->getEngine()->presetTouched();
        this->param_06_lastValue = this->param_06_value;
    }

    this->p_01_in3_number_set(v);
}

void param_07_value_set(number v) {
    v = this->param_07_value_constrain(v);
    this->param_07_value = v;
    this->sendParameter(6, false);

    if (this->param_07_value != this->param_07_lastValue) {
        this->getEngine()->presetTouched();
        this->param_07_lastValue = this->param_07_value;
    }

    this->p_01_in4_number_set(v);
}

void inport_01_value_bang_bang() {
    this->inport_01_out_bang_bang();
}

void inport_01_value_number_set(number v) {
    this->inport_01_out_number_set(v);
}

void inport_01_value_list_set(const list& v) {
    this->inport_01_out_list_set(v);
}

void message_01_listin_list_set(const list& v) {
    this->message_01_set_set(v);
}

void message_01_listin_number_set(number v) {
    this->message_01_set_set(v);
}

void message_01_listin_bang_bang() {
    this->message_01_trigger_bang();
}

void loadbang_01_startupbang_bang() {
    this->loadbang_01_output_bang();
}

number msToSamps(MillisecondTime ms, number sampleRate) {
    return ms * sampleRate * 0.001;
}

MillisecondTime sampsToMs(SampleIndex samps) {
    return samps * (this->invsr * 1000);
}

Index getMaxBlockSize() const {
    return this->maxvs;
}

number getSampleRate() const {
    return this->sr;
}

bool hasFixedVectorSize() const {
    return false;
}

Index getNumInputChannels() const {
    return 2;
}

Index getNumOutputChannels() const {
    return 2;
}

void allocateDataRefs() {
    this->p_01->allocateDataRefs();
    this->cycle_tilde_01_buffer->requestSize(16384, 1);
    this->cycle_tilde_01_buffer->setSampleRate(this->sr);
    this->cycle_tilde_02_buffer->requestSize(16384, 1);
    this->cycle_tilde_02_buffer->setSampleRate(this->sr);
    this->cycle_tilde_01_buffer = this->cycle_tilde_01_buffer->allocateIfNeeded();
    this->cycle_tilde_02_buffer = this->cycle_tilde_02_buffer->allocateIfNeeded();

    if (this->RNBODefaultSinus->hasRequestedSize()) {
        if (this->RNBODefaultSinus->wantsFill())
            this->fillRNBODefaultSinus(this->RNBODefaultSinus);

        this->getEngine()->sendDataRefUpdated(0);
    }

    this->data_01_buffer = this->data_01_buffer->allocateIfNeeded();
    this->groove_01_buffer = this->groove_01_buffer->allocateIfNeeded();

    if (this->rnbuff1->hasRequestedSize()) {
        if (this->rnbuff1->wantsFill())
            this->zeroDataRef(this->rnbuff1);

        this->getEngine()->sendDataRefUpdated(1);
    }
}

void initializeObjects() {
    this->data_01_init();
    this->message_01_init();
    this->p_01->initializeObjects();
}

void sendOutlet(OutletIndex index, ParameterValue value) {
    this->getEngine()->sendOutlet(this, index, value);
}

void startup() {
    this->updateTime(this->getEngine()->getCurrentTime());
    this->p_01->startup();
    this->getEngine()->scheduleClockEvent(this, -871642103, 0 + this->_currentTime);;

    {
        this->scheduleParamInit(0, 0);
    }

    {
        this->scheduleParamInit(1, 0);
    }

    {
        this->scheduleParamInit(2, 0);
    }

    {
        this->scheduleParamInit(3, 0);
    }

    {
        this->scheduleParamInit(5, 0);
    }

    {
        this->scheduleParamInit(6, 0);
    }

    this->processParamInitEvents();
}

static number param_01_value_constrain(number v) {
    v = (v > 440 ? 440 : (v < 220 ? 220 : v));
    return v;
}

void slide_tilde_01_x_set(number v) {
    this->slide_tilde_01_x = v;
}

static number param_02_value_constrain(number v) {
    v = (v > 440 ? 440 : (v < 220 ? 220 : v));
    return v;
}

void slide_tilde_02_x_set(number v) {
    this->slide_tilde_02_x = v;
}

static number param_03_value_constrain(number v) {
    v = (v > 0.5 ? 0.5 : (v < 0 ? 0 : v));
    return v;
}

void slide_tilde_03_x_set(number v) {
    this->slide_tilde_03_x = v;
}

static number param_04_value_constrain(number v) {
    v = (v > 0.5 ? 0.5 : (v < 0 ? 0 : v));
    return v;
}

void slide_tilde_04_x_set(number v) {
    this->slide_tilde_04_x = v;
}

static number param_05_value_constrain(number v) {
    v = (v > 2 ? 2 : (v < 0.5 ? 0.5 : v));
    return v;
}

void groove_01_rate_auto_set(number v) {
    this->groove_01_rate_auto = v;
}

void trigger_01_out2_set(number v) {
    this->groove_01_rate_auto_set(v);
}

void groove_01_rate_bang_bang() {
    this->groove_01_changeIncomingInSamples = this->sampleOffsetIntoNextAudioBuffer + 1;
    this->groove_01_incomingChange = 1;
}

void trigger_01_out1_bang() {
    this->groove_01_rate_bang_bang();
}

void trigger_01_input_number_set(number v) {
    this->trigger_01_out2_set(v);
    this->trigger_01_out1_bang();
}

static number param_06_value_constrain(number v) {
    v = (v > 2000 ? 2000 : (v < 0 ? 0 : v));
    return v;
}

void p_01_in3_number_set(number v) {
    this->p_01->updateTime(this->_currentTime);
    this->p_01->eventinlet_01_out1_number_set(v);
}

static number param_07_value_constrain(number v) {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

void p_01_in4_number_set(number v) {
    this->p_01->updateTime(this->_currentTime);
    this->p_01->eventinlet_02_out1_number_set(v);
}

void unpack_01_out5_bang() {
    number v = this->unpack_01_out5;
    this->param_05_value_set(v);
}

void unpack_01_out4_bang() {
    number v = this->unpack_01_out4;
    this->param_04_value_set(v);
}

void unpack_01_out3_bang() {
    number v = this->unpack_01_out3;
    this->param_03_value_set(v);
}

void unpack_01_out2_bang() {
    number v = this->unpack_01_out2;
    this->param_02_value_set(v);
}

void unpack_01_out1_bang() {
    number v = this->unpack_01_out1;
    this->param_01_value_set(v);
}

void unpack_01_input_bang_bang() {
    this->unpack_01_out5_bang();
    this->unpack_01_out4_bang();
    this->unpack_01_out3_bang();
    this->unpack_01_out2_bang();
    this->unpack_01_out1_bang();
}

void inport_01_out_bang_bang() {
    this->unpack_01_input_bang_bang();
}

void unpack_01_out5_set(number v) {
    this->unpack_01_out5 = v;
    this->param_05_value_set(v);
}

void unpack_01_out4_set(number v) {
    this->unpack_01_out4 = v;
    this->param_04_value_set(v);
}

void unpack_01_out3_set(number v) {
    this->unpack_01_out3 = v;
    this->param_03_value_set(v);
}

void unpack_01_out2_set(number v) {
    this->unpack_01_out2 = v;
    this->param_02_value_set(v);
}

void unpack_01_out1_set(number v) {
    this->unpack_01_out1 = v;
    this->param_01_value_set(v);
}

void unpack_01_input_list_set(const list& v) {
    if (v->length > 4)
        this->unpack_01_out5_set(v[4]);

    if (v->length > 3)
        this->unpack_01_out4_set(v[3]);

    if (v->length > 2)
        this->unpack_01_out3_set(v[2]);

    if (v->length > 1)
        this->unpack_01_out2_set(v[1]);

    if (v->length > 0)
        this->unpack_01_out1_set(v[0]);
}

void inport_01_out_number_set(number v) {
    {
        list converted = {v};
        this->unpack_01_input_list_set(converted);
    }
}

void inport_01_out_list_set(const list& v) {
    this->unpack_01_input_list_set(v);
}

void message_01_set_set(const list& v) {
    this->message_01_set = jsCreateListCopy(v);
    this->getEngine()->sendListMessage(TAG("listout"), TAG("message_obj-63"), v, this->_currentTime);
}

void message_01_out_set(const list& ) {}

void message_01_trigger_bang() {
    this->message_01_out_set(this->message_01_set);
}

void trigger_03_out3_set(number ) {}

void trigger_03_out2_set(number ) {}

void trigger_03_out1_set(number ) {}

void trigger_03_input_bang_bang() {
    this->trigger_03_out3_set(1);
    this->trigger_03_out2_set(127);
    this->trigger_03_out1_set(60);
}

void trigger_02_out2_bang() {
    this->trigger_03_input_bang_bang();
}

void trigger_02_out1_bang() {
    this->message_01_trigger_bang();
}

void trigger_02_input_bang_bang() {
    this->trigger_02_out2_bang();
    this->trigger_02_out1_bang();
}

void loadbang_01_output_bang() {
    this->trigger_02_input_bang_bang();
}

void midiout_01_midiin_set(number v) {
    int vi = (int)(v);

    if (vi == 0xF6 || (vi >= MIDI_Clock && vi <= MIDI_Reset && vi != 0xF9 && vi != 0xFD)) {
        this->getEngine()->sendMidiEvent(this->midiout_01_port, vi, 0, 0, this->_currentTime);
        return;
    }

    this->midiout_01_currentStatus = parseMidi(this->midiout_01_currentStatus, vi, this->midiout_01_status);
    bool clearSysex = true;

    switch ((int)this->midiout_01_currentStatus) {
    case MIDI_StatusByteReceived:
        {
        this->midiout_01_status = v;
        this->midiout_01_byte1 = -1;
        break;
        }
    case MIDI_SecondByteReceived:
        {
        this->midiout_01_byte1 = v;
        break;
        }
    case MIDI_ProgramChange:
    case MIDI_ChannelPressure:
    case MIDI_QuarterFrame:
    case MIDI_SongSel:
        {
        this->midiout_01_byte1 = v;

        this->getEngine()->sendMidiEvent(
            this->midiout_01_port,
            this->midiout_01_status,
            this->midiout_01_byte1,
            0,
            this->_currentTime
        );

        break;
        }
    case MIDI_NoteOff:
    case MIDI_NoteOn:
    case MIDI_Aftertouch:
    case MIDI_CC:
    case MIDI_PitchBend:
    case MIDI_SongPos:
    case MIDI_Generic:
        {
        this->getEngine()->sendMidiEvent(
            this->midiout_01_port,
            this->midiout_01_status,
            this->midiout_01_byte1,
            v,
            this->_currentTime
        );

        break;
        }
    case MIDI_Sysex_Started:
        {
        this->midiout_01_sysex->push(vi);
        clearSysex = false;
        break;
        }
    case MIDI_Sysex_Complete:
        {
        this->midiout_01_sysex->push(vi);
        this->getEngine()->sendMidiEventList(this->midiout_01_port, this->midiout_01_sysex, this->_currentTime);
        break;
        }
    case MIDI_InvalidByte:
        {
        break;
        }
    default:
        {
        break;
        }
    }

    if ((bool)(clearSysex) && this->midiout_01_sysex->length > 0) {
        this->midiout_01_sysex = {};
    }
}

void midiin_01_midiout_set(number v) {
    this->midiout_01_midiin_set(v);
}

void midiin_01_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
    RNBO_UNUSED(port);
    RNBO_UNUSED(channel);
    RNBO_UNUSED(status);
    Index i;

    for (i = 0; i < length; i++) {
        this->midiin_01_midiout_set(data[i]);
    }
}

void slide_tilde_01_perform(number x, number up, number down, SampleValue * out1, Index n) {
    RNBO_UNUSED(down);
    RNBO_UNUSED(up);
    auto __slide_tilde_01_prev = this->slide_tilde_01_prev;
    auto iup = this->safediv(1., this->maximum(1., rnbo_abs(200)));
    auto idown = this->safediv(1., this->maximum(1., rnbo_abs(200)));
    Index i;

    for (i = 0; i < n; i++) {
        number temp = x - __slide_tilde_01_prev;
        __slide_tilde_01_prev = __slide_tilde_01_prev + ((x > __slide_tilde_01_prev ? iup : idown)) * temp;
        out1[(Index)i] = __slide_tilde_01_prev;
    }

    this->slide_tilde_01_prev = __slide_tilde_01_prev;
}

void cycle_tilde_01_perform(
    const Sample * frequency,
    number phase_offset,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    RNBO_UNUSED(phase_offset);
    auto __cycle_tilde_01_f2i = this->cycle_tilde_01_f2i;
    auto __cycle_tilde_01_buffer = this->cycle_tilde_01_buffer;
    auto __cycle_tilde_01_phasei = this->cycle_tilde_01_phasei;
    Index i;

    for (i = 0; i < n; i++) {
        {
            uint32_t uint_phase;

            {
                {
                    uint_phase = __cycle_tilde_01_phasei;
                }
            }

            uint32_t idx = (uint32_t)(uint32_rshift(uint_phase, 18));
            number frac = ((BinOpInt)((BinOpInt)uint_phase & (BinOpInt)262143)) * 3.81471181759574e-6;
            number y0 = __cycle_tilde_01_buffer[(Index)idx];
            number y1 = __cycle_tilde_01_buffer[(Index)((BinOpInt)(idx + 1) & (BinOpInt)16383)];
            number y = y0 + frac * (y1 - y0);

            {
                uint32_t pincr = (uint32_t)(uint32_trunc(frequency[(Index)i] * __cycle_tilde_01_f2i));
                __cycle_tilde_01_phasei = uint32_add(__cycle_tilde_01_phasei, pincr);
            }

            out1[(Index)i] = y;
            out2[(Index)i] = uint_phase * 0.232830643653869629e-9;
            continue;
        }
    }

    this->cycle_tilde_01_phasei = __cycle_tilde_01_phasei;
}

void slide_tilde_02_perform(number x, number up, number down, SampleValue * out1, Index n) {
    RNBO_UNUSED(down);
    RNBO_UNUSED(up);
    auto __slide_tilde_02_prev = this->slide_tilde_02_prev;
    auto iup = this->safediv(1., this->maximum(1., rnbo_abs(200)));
    auto idown = this->safediv(1., this->maximum(1., rnbo_abs(200)));
    Index i;

    for (i = 0; i < n; i++) {
        number temp = x - __slide_tilde_02_prev;
        __slide_tilde_02_prev = __slide_tilde_02_prev + ((x > __slide_tilde_02_prev ? iup : idown)) * temp;
        out1[(Index)i] = __slide_tilde_02_prev;
    }

    this->slide_tilde_02_prev = __slide_tilde_02_prev;
}

void cycle_tilde_02_perform(
    const Sample * frequency,
    number phase_offset,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    RNBO_UNUSED(phase_offset);
    auto __cycle_tilde_02_f2i = this->cycle_tilde_02_f2i;
    auto __cycle_tilde_02_buffer = this->cycle_tilde_02_buffer;
    auto __cycle_tilde_02_phasei = this->cycle_tilde_02_phasei;
    Index i;

    for (i = 0; i < n; i++) {
        {
            uint32_t uint_phase;

            {
                {
                    uint_phase = __cycle_tilde_02_phasei;
                }
            }

            uint32_t idx = (uint32_t)(uint32_rshift(uint_phase, 18));
            number frac = ((BinOpInt)((BinOpInt)uint_phase & (BinOpInt)262143)) * 3.81471181759574e-6;
            number y0 = __cycle_tilde_02_buffer[(Index)idx];
            number y1 = __cycle_tilde_02_buffer[(Index)((BinOpInt)(idx + 1) & (BinOpInt)16383)];
            number y = y0 + frac * (y1 - y0);

            {
                uint32_t pincr = (uint32_t)(uint32_trunc(frequency[(Index)i] * __cycle_tilde_02_f2i));
                __cycle_tilde_02_phasei = uint32_add(__cycle_tilde_02_phasei, pincr);
            }

            out1[(Index)i] = y;
            out2[(Index)i] = uint_phase * 0.232830643653869629e-9;
            continue;
        }
    }

    this->cycle_tilde_02_phasei = __cycle_tilde_02_phasei;
}

void slide_tilde_03_perform(number x, number up, number down, SampleValue * out1, Index n) {
    RNBO_UNUSED(down);
    RNBO_UNUSED(up);
    auto __slide_tilde_03_prev = this->slide_tilde_03_prev;
    auto iup = this->safediv(1., this->maximum(1., rnbo_abs(200)));
    auto idown = this->safediv(1., this->maximum(1., rnbo_abs(200)));
    Index i;

    for (i = 0; i < n; i++) {
        number temp = x - __slide_tilde_03_prev;
        __slide_tilde_03_prev = __slide_tilde_03_prev + ((x > __slide_tilde_03_prev ? iup : idown)) * temp;
        out1[(Index)i] = __slide_tilde_03_prev;
    }

    this->slide_tilde_03_prev = __slide_tilde_03_prev;
}

void dspexpr_01_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < n; i++) {
        out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
    }
}

void slide_tilde_04_perform(number x, number up, number down, SampleValue * out1, Index n) {
    RNBO_UNUSED(down);
    RNBO_UNUSED(up);
    auto __slide_tilde_04_prev = this->slide_tilde_04_prev;
    auto iup = this->safediv(1., this->maximum(1., rnbo_abs(200)));
    auto idown = this->safediv(1., this->maximum(1., rnbo_abs(200)));
    Index i;

    for (i = 0; i < n; i++) {
        number temp = x - __slide_tilde_04_prev;
        __slide_tilde_04_prev = __slide_tilde_04_prev + ((x > __slide_tilde_04_prev ? iup : idown)) * temp;
        out1[(Index)i] = __slide_tilde_04_prev;
    }

    this->slide_tilde_04_prev = __slide_tilde_04_prev;
}

void dspexpr_03_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < n; i++) {
        out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
    }
}

void dspexpr_02_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < n; i++) {
        out1[(Index)i] = in1[(Index)i] + in2[(Index)i];//#map:_###_obj_###_:1
    }
}

void groove_01_perform(
    number rate_auto,
    number begin,
    number end,
    SampleValue * out1,
    SampleValue * sync,
    Index n
) {
    RNBO_UNUSED(out1);
    RNBO_UNUSED(end);
    RNBO_UNUSED(begin);
    auto __groove_01_crossfade = this->groove_01_crossfade;
    auto __groove_01_loop = this->groove_01_loop;
    auto __groove_01_playStatus = this->groove_01_playStatus;
    auto __groove_01_readIndex = this->groove_01_readIndex;
    auto __groove_01_incomingChange = this->groove_01_incomingChange;
    auto __groove_01_changeIncomingInSamples = this->groove_01_changeIncomingInSamples;
    auto __groove_01_buffer = this->groove_01_buffer;
    SampleArray<1> out = {out1};
    SampleIndex bufferLength = (SampleIndex)(__groove_01_buffer->getSize());
    Index i = 0;

    if (bufferLength > 1) {
        auto effectiveChannels = this->minimum(__groove_01_buffer->getChannels(), 1);
        number srMult = 0.001 * __groove_01_buffer->getSampleRate();
        number srInv = (number)1 / this->samplerate();
        number rateMult = __groove_01_buffer->getSampleRate() * srInv;

        for (; i < n; i++) {
            Index channel = 0;
            number offset = 0;
            number loopMin = 0 * srMult;
            loopMin = (loopMin > bufferLength - 1 ? bufferLength - 1 : (loopMin < 0 ? 0 : loopMin));
            number loopMax = bufferLength;
            loopMax = (loopMax > bufferLength ? bufferLength : (loopMax < 0 ? 0 : loopMax));

            if (loopMin >= loopMax) {
                offset = loopMax;
                loopMax = bufferLength;
                loopMin -= offset;
            }

            number loopLength = loopMax - loopMin;
            number currentRate = rate_auto * rateMult;
            number currentSync = 0;

            if (__groove_01_changeIncomingInSamples > 0) {
                __groove_01_changeIncomingInSamples--;

                if (__groove_01_changeIncomingInSamples <= 0) {
                    if (__groove_01_incomingChange == 1) {
                        if (currentRate < 0) {
                            __groove_01_readIndex = loopMax - 1;
                        } else {
                            __groove_01_readIndex = loopMin;
                        }

                        __groove_01_playStatus = 1;
                    } else if (__groove_01_incomingChange == 0) {
                        __groove_01_playStatus = 0;
                    }

                    __groove_01_incomingChange = 2;
                }
            }

            if (loopLength > 0) {
                if (currentRate != 0) {
                    if (__groove_01_playStatus == 1) {
                        if ((bool)(__groove_01_loop)) {
                            while (__groove_01_readIndex < loopMin) {
                                __groove_01_readIndex += loopLength;
                            }

                            while (__groove_01_readIndex >= loopMax) {
                                __groove_01_readIndex -= loopLength;
                            }
                        } else if (__groove_01_readIndex >= loopMax || __groove_01_readIndex < loopMin) {
                            __groove_01_playStatus = 0;
                            break;
                        }

                        for (; channel < effectiveChannels; channel++) {
                            number outSample = (currentRate == 1 ? this->groove_01_getSample((Index)(channel), trunc(__groove_01_readIndex), offset, bufferLength) : this->groove_01_interpolatedSample(
                                (Index)(channel),
                                __groove_01_readIndex,
                                loopMax,
                                loopLength,
                                offset,
                                bufferLength
                            ));

                            if (__groove_01_crossfade > 0) {
                                out[(Index)channel][(Index)i] = this->groove_01_crossfadedSample(
                                    outSample,
                                    __groove_01_readIndex,
                                    (Index)(channel),
                                    currentRate,
                                    loopMin,
                                    loopMax,
                                    loopLength,
                                    offset,
                                    bufferLength
                                );
                            } else {
                                out[(Index)channel][(Index)i] = outSample;
                            }
                        }

                        __groove_01_readIndex += currentRate;
                    }
                }
            }

            for (; channel < 1; channel++) {
                if (__groove_01_playStatus <= 0)
                    sync[(Index)i] = 0;

                out[(Index)channel][(Index)i] = 0;
            }
        }
    }

    for (; i < n; i++) {
        if (__groove_01_playStatus <= 0)
            sync[(Index)i] = 0;

        for (number channel = 0; channel < 1; channel++) {
            out[(Index)channel][(Index)i] = 0;
        }
    }

    this->groove_01_changeIncomingInSamples = __groove_01_changeIncomingInSamples;
    this->groove_01_incomingChange = __groove_01_incomingChange;
    this->groove_01_readIndex = __groove_01_readIndex;
    this->groove_01_playStatus = __groove_01_playStatus;
}

void p_01_perform(
    const SampleValue * in1,
    const SampleValue * in2,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    // subpatcher: filters
    ConstSampleArray<2> ins = {in1, in2};

    SampleArray<2> outs = {out1, out2};
    this->p_01->process(ins, 2, outs, 2, n);
}

void signaladder_01_perform(
    const SampleValue * in1,
    const SampleValue * in2,
    const SampleValue * in3,
    SampleValue * out,
    Index n
) {
    Index i;

    for (i = 0; i < n; i++) {
        out[(Index)i] = in1[(Index)i] + in2[(Index)i] + in3[(Index)i];
    }
}

void signaladder_02_perform(
    const SampleValue * in1,
    const SampleValue * in2,
    const SampleValue * in3,
    SampleValue * out,
    Index n
) {
    Index i;

    for (i = 0; i < n; i++) {
        out[(Index)i] = in1[(Index)i] + in2[(Index)i] + in3[(Index)i];
    }
}

void lores_03_perform(
    number cutoff,
    number resonance,
    const SampleValue * input,
    SampleValue * out,
    Index n
) {
    RNBO_UNUSED(resonance);
    RNBO_UNUSED(cutoff);
    auto __lores_03_y_2 = this->lores_03_y_2;
    auto __lores_03_y_1 = this->lores_03_y_1;
    auto __lores_03_x_0 = this->lores_03_x_0;
    auto __lores_03_b_0 = this->lores_03_b_0;
    auto __lores_03_a_1 = this->lores_03_a_1;
    auto __lores_03_a_2 = this->lores_03_a_2;
    auto __lores_03_last_freq_calc = this->lores_03_last_freq_calc;
    auto __lores_03_last_res_calc = this->lores_03_last_res_calc;
    auto __lores_03_last_frequency = this->lores_03_last_frequency;
    auto __lores_03_last_resonance = this->lores_03_last_resonance;

    for (Index i = 0; i < n; i++) {
        if (0 != __lores_03_last_resonance || 0 != __lores_03_last_frequency) {
            __lores_03_last_res_calc = rnbo_exp(0 * 0.125) * 0.882497;
            __lores_03_last_freq_calc = rnbo_cos(2.0 * pi01() / this->sr * 0);
            __lores_03_last_resonance = 0;
            __lores_03_last_frequency = 0;
        }

        number res_temp = __lores_03_last_res_calc;
        number freq_temp = __lores_03_last_freq_calc;
        __lores_03_a_2 = res_temp * res_temp;
        __lores_03_a_1 = -2.0 * res_temp * freq_temp;
        __lores_03_b_0 = 1.0 + __lores_03_a_1 + __lores_03_a_2;
        __lores_03_x_0 = input[(Index)i];
        number y_0 = __lores_03_x_0 * __lores_03_b_0 - __lores_03_y_1 * __lores_03_a_1 - __lores_03_y_2 * __lores_03_a_2;
        __lores_03_y_2 = __lores_03_y_1;
        __lores_03_y_1 = y_0;
        out[(Index)i] = y_0;
    }

    this->lores_03_last_resonance = __lores_03_last_resonance;
    this->lores_03_last_frequency = __lores_03_last_frequency;
    this->lores_03_last_res_calc = __lores_03_last_res_calc;
    this->lores_03_last_freq_calc = __lores_03_last_freq_calc;
    this->lores_03_a_2 = __lores_03_a_2;
    this->lores_03_a_1 = __lores_03_a_1;
    this->lores_03_b_0 = __lores_03_b_0;
    this->lores_03_x_0 = __lores_03_x_0;
    this->lores_03_y_1 = __lores_03_y_1;
    this->lores_03_y_2 = __lores_03_y_2;
}

void stackprotect_perform(Index n) {
    RNBO_UNUSED(n);
    auto __stackprotect_count = this->stackprotect_count;
    __stackprotect_count = 0;
    this->stackprotect_count = __stackprotect_count;
}

void data_01_srout_set(number ) {}

void data_01_chanout_set(number ) {}

void data_01_sizeout_set(number v) {
    this->data_01_sizeout = v;
}

void lores_03_resonance_setter(number v) {
    if (v < 0.0) {
        v = 0.0;
    } else if (v >= 1.0) {
        v = 1.0 - 1E-20;
    }

    this->lores_03_resonance = v;
}

void param_01_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_01_value;
}

void param_01_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_01_value_set(preset["value"]);
}

number cycle_tilde_01_ph_next(number freq, number reset) {
    {
        {
            if (reset >= 0.)
                this->cycle_tilde_01_ph_currentPhase = reset;
        }
    }

    number pincr = freq * this->cycle_tilde_01_ph_conv;

    if (this->cycle_tilde_01_ph_currentPhase < 0.)
        this->cycle_tilde_01_ph_currentPhase = 1. + this->cycle_tilde_01_ph_currentPhase;

    if (this->cycle_tilde_01_ph_currentPhase > 1.)
        this->cycle_tilde_01_ph_currentPhase = this->cycle_tilde_01_ph_currentPhase - 1.;

    number tmp = this->cycle_tilde_01_ph_currentPhase;
    this->cycle_tilde_01_ph_currentPhase += pincr;
    return tmp;
}

void cycle_tilde_01_ph_reset() {
    this->cycle_tilde_01_ph_currentPhase = 0;
}

void cycle_tilde_01_ph_dspsetup() {
    this->cycle_tilde_01_ph_conv = (number)1 / this->sr;
}

void cycle_tilde_01_dspsetup(bool force) {
    if ((bool)(this->cycle_tilde_01_setupDone) && (bool)(!(bool)(force)))
        return;

    this->cycle_tilde_01_phasei = 0;
    this->cycle_tilde_01_f2i = (number)4294967296 / this->samplerate();
    this->cycle_tilde_01_wrap = (long)(this->cycle_tilde_01_buffer->getSize()) - 1;
    this->cycle_tilde_01_setupDone = true;
    this->cycle_tilde_01_ph_dspsetup();
}

void cycle_tilde_01_bufferUpdated() {
    this->cycle_tilde_01_wrap = (long)(this->cycle_tilde_01_buffer->getSize()) - 1;
}

number cycle_tilde_02_ph_next(number freq, number reset) {
    {
        {
            if (reset >= 0.)
                this->cycle_tilde_02_ph_currentPhase = reset;
        }
    }

    number pincr = freq * this->cycle_tilde_02_ph_conv;

    if (this->cycle_tilde_02_ph_currentPhase < 0.)
        this->cycle_tilde_02_ph_currentPhase = 1. + this->cycle_tilde_02_ph_currentPhase;

    if (this->cycle_tilde_02_ph_currentPhase > 1.)
        this->cycle_tilde_02_ph_currentPhase = this->cycle_tilde_02_ph_currentPhase - 1.;

    number tmp = this->cycle_tilde_02_ph_currentPhase;
    this->cycle_tilde_02_ph_currentPhase += pincr;
    return tmp;
}

void cycle_tilde_02_ph_reset() {
    this->cycle_tilde_02_ph_currentPhase = 0;
}

void cycle_tilde_02_ph_dspsetup() {
    this->cycle_tilde_02_ph_conv = (number)1 / this->sr;
}

void cycle_tilde_02_dspsetup(bool force) {
    if ((bool)(this->cycle_tilde_02_setupDone) && (bool)(!(bool)(force)))
        return;

    this->cycle_tilde_02_phasei = 0;
    this->cycle_tilde_02_f2i = (number)4294967296 / this->samplerate();
    this->cycle_tilde_02_wrap = (long)(this->cycle_tilde_02_buffer->getSize()) - 1;
    this->cycle_tilde_02_setupDone = true;
    this->cycle_tilde_02_ph_dspsetup();
}

void cycle_tilde_02_bufferUpdated() {
    this->cycle_tilde_02_wrap = (long)(this->cycle_tilde_02_buffer->getSize()) - 1;
}

void param_02_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_02_value;
}

void param_02_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_02_value_set(preset["value"]);
}

void param_03_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_03_value;
}

void param_03_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_03_value_set(preset["value"]);
}

void param_04_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_04_value;
}

void param_04_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_04_value_set(preset["value"]);
}

void data_01_init() {
    this->data_01_buffer->setWantsFill(true);
}

Index data_01_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    number size = 0;
    return (Index)(size);
}

void data_01_dspsetup(bool force) {
    if ((bool)(this->data_01_setupDone) && (bool)(!(bool)(force)))
        return;

    if (this->data_01_sizemode == 2) {
        this->data_01_buffer = this->data_01_buffer->setSize((Index)(this->mstosamps(this->data_01_sizems)));
        updateDataRef(this, this->data_01_buffer);
    } else if (this->data_01_sizemode == 3) {
        this->data_01_buffer = this->data_01_buffer->setSize(this->data_01_evaluateSizeExpr(this->samplerate(), this->vectorsize()));
        updateDataRef(this, this->data_01_buffer);
    }

    this->data_01_setupDone = true;
}

void data_01_bufferUpdated() {
    this->data_01_report();
}

void data_01_report() {
    this->data_01_srout_set(this->data_01_buffer->getSampleRate());
    this->data_01_chanout_set(this->data_01_buffer->getChannels());
    this->data_01_sizeout_set(this->data_01_buffer->getSize());
}

void param_05_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_05_value;
}

void param_05_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_05_value_set(preset["value"]);
}

number groove_01_getSample(
    Index channel,
    SampleIndex index,
    SampleIndex offset,
    SampleIndex bufferLength
) {
    if (offset > 0) {
        index += offset;

        if (index >= bufferLength)
            index -= bufferLength;
    }

    return this->groove_01_buffer->getSample(channel, index);
}

number groove_01_interpolatedSample(
    Index channel,
    number index,
    SampleIndex end,
    SampleIndex length,
    SampleIndex offset,
    SampleIndex bufferLength
) {
    SampleIndex index1 = (SampleIndex)(trunc(index));
    number i_x = index - index1;
    number i_1px = 1. + i_x;
    number i_1mx = 1. - i_x;
    number i_2mx = 2. - i_x;
    number i_a = i_1mx * i_2mx;
    number i_b = i_1px * i_x;
    number i_p1 = -.1666667 * i_a * i_x;
    number i_p2 = .5 * i_1px * i_a;
    number i_p3 = .5 * i_b * i_2mx;
    number i_p4 = -.1666667 * i_b * i_1mx;
    SampleIndex index2 = (SampleIndex)(index1 + 1);

    if (index2 >= end)
        index2 -= length;

    SampleIndex index3 = (SampleIndex)(index1 + 2);

    if (index3 >= end)
        index3 -= length;

    SampleIndex index4 = (SampleIndex)(index1 + 3);

    if (index4 >= end)
        index4 -= length;

    return this->groove_01_getSample(channel, index1, offset, bufferLength) * i_p1 + this->groove_01_getSample(channel, index2, offset, bufferLength) * i_p2 + this->groove_01_getSample(channel, index3, offset, bufferLength) * i_p3 + this->groove_01_getSample(channel, index4, offset, bufferLength) * i_p4;
}

number groove_01_crossfadedSample(
    SampleValue out,
    number readIndex,
    Index channel,
    number rate,
    number loopMin,
    number loopMax,
    number loopLength,
    number offset,
    number bufferLength
) {
    auto crossFadeStart1 = this->maximum(loopMin - this->groove_01_crossfadeInSamples, 0);
    auto crossFadeEnd1 = this->minimum(crossFadeStart1 + this->groove_01_crossfadeInSamples, bufferLength);
    number crossFadeStart2 = crossFadeStart1 + loopLength;
    auto crossFadeEnd2 = this->minimum(crossFadeEnd1 + loopLength, bufferLength);
    number crossFadeLength = crossFadeEnd2 - crossFadeStart2;

    if (crossFadeLength > 0) {
        crossFadeEnd1 = crossFadeStart1 + crossFadeLength;
        number diff = -1;
        number addFactor = 0;

        if (readIndex >= crossFadeStart2) {
            diff = readIndex - crossFadeStart2;
            addFactor = -1;
        } else if (readIndex < crossFadeEnd1) {
            diff = crossFadeEnd1 - readIndex + loopMax - crossFadeStart2;
            addFactor = 1;
        }

        if (diff >= 0) {
            number out2ReadIndex = readIndex + loopLength * addFactor;
            number out2 = (rate == 1 ? this->groove_01_getSample(channel, trunc(out2ReadIndex), offset, bufferLength) : this->groove_01_interpolatedSample(channel, out2ReadIndex, loopMax, loopLength, offset, bufferLength));
            number out2Factor = diff / crossFadeLength;
            number out1Factor = 1 - out2Factor;
            return out * out1Factor + out2 * out2Factor;
        }
    }

    return out;
}

void groove_01_dspsetup(bool force) {
    if ((bool)(this->groove_01_setupDone) && (bool)(!(bool)(force)))
        return;

    this->groove_01_crossfadeInSamples = this->mstosamps(this->groove_01_crossfade);
    this->groove_01_setupDone = true;
}

void param_06_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_06_value;
}

void param_06_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_06_value_set(preset["value"]);
}

void lores_03_reset() {
    this->lores_03_y_1 = 0;
    this->lores_03_y_2 = 0;
    this->lores_03_last_resonance = 0;
    this->lores_03_last_frequency = 0;
    this->lores_03_last_res_calc = 0;
    this->lores_03_last_freq_calc = 0;
}

void lores_03_dspsetup(bool force) {
    if ((bool)(this->lores_03_setupDone) && (bool)(!(bool)(force)))
        return;

    this->lores_03_reset();
    this->lores_03_setupDone = true;
}

void message_01_init() {
    this->message_01_set_set({42});
}

void param_07_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_07_value;
}

void param_07_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_07_value_set(preset["value"]);
}

Index globaltransport_getSampleOffset(MillisecondTime time) {
    return this->mstosamps(this->maximum(0, time - this->getEngine()->getCurrentTime()));
}

number globaltransport_getTempoAtSample(SampleIndex sampleOffset) {
    return (sampleOffset >= 0 && sampleOffset < this->vs ? this->globaltransport_tempo[(Index)sampleOffset] : this->globaltransport_lastTempo);
}

number globaltransport_getStateAtSample(SampleIndex sampleOffset) {
    return (sampleOffset >= 0 && sampleOffset < this->vs ? this->globaltransport_state[(Index)sampleOffset] : this->globaltransport_lastState);
}

number globaltransport_getState(MillisecondTime time) {
    return this->globaltransport_getStateAtSample(this->globaltransport_getSampleOffset(time));
}

number globaltransport_getBeatTime(MillisecondTime time) {
    number i = 2;

    while (i < this->globaltransport_beatTimeChanges->length && this->globaltransport_beatTimeChanges[(Index)(i + 1)] <= time) {
        i += 2;
    }

    i -= 2;
    number beatTimeBase = this->globaltransport_beatTimeChanges[(Index)i];

    if (this->globaltransport_getState(time) == 0)
        return beatTimeBase;

    number beatTimeBaseMsTime = this->globaltransport_beatTimeChanges[(Index)(i + 1)];
    number diff = time - beatTimeBaseMsTime;
    return beatTimeBase + this->mstobeats(diff);
}

bool globaltransport_setTempo(MillisecondTime time, number tempo, bool notify) {
    if ((bool)(notify)) {
        this->processTempoEvent(time, tempo);
        this->globaltransport_notify = true;
    } else {
        Index offset = (Index)(this->globaltransport_getSampleOffset(time));

        if (this->globaltransport_getTempoAtSample(offset) != tempo) {
            this->globaltransport_beatTimeChanges->push(this->globaltransport_getBeatTime(time));
            this->globaltransport_beatTimeChanges->push(time);
            fillSignal(this->globaltransport_tempo, this->vs, tempo, offset);
            this->globaltransport_lastTempo = tempo;
            this->globaltransport_tempoNeedsReset = true;
            return true;
        }
    }

    return false;
}

number globaltransport_getTempo(MillisecondTime time) {
    return this->globaltransport_getTempoAtSample(this->globaltransport_getSampleOffset(time));
}

bool globaltransport_setState(MillisecondTime time, number state, bool notify) {
    if ((bool)(notify)) {
        this->processTransportEvent(time, TransportState(state));
        this->globaltransport_notify = true;
    } else {
        Index offset = (Index)(this->globaltransport_getSampleOffset(time));

        if (this->globaltransport_getStateAtSample(offset) != state) {
            fillSignal(this->globaltransport_state, this->vs, state, offset);
            this->globaltransport_lastState = TransportState(state);
            this->globaltransport_stateNeedsReset = true;

            if (state == 0) {
                this->globaltransport_beatTimeChanges->push(this->globaltransport_getBeatTime(time));
                this->globaltransport_beatTimeChanges->push(time);
            }

            return true;
        }
    }

    return false;
}

bool globaltransport_setBeatTime(MillisecondTime time, number beattime, bool notify) {
    if ((bool)(notify)) {
        this->processBeatTimeEvent(time, beattime);
        this->globaltransport_notify = true;
        return false;
    } else {
        bool beatTimeHasChanged = false;
        float oldBeatTime = (float)(this->globaltransport_getBeatTime(time));
        float newBeatTime = (float)(beattime);

        if (oldBeatTime != newBeatTime) {
            beatTimeHasChanged = true;
        }

        this->globaltransport_beatTimeChanges->push(beattime);
        this->globaltransport_beatTimeChanges->push(time);
        return beatTimeHasChanged;
    }
}

number globaltransport_getBeatTimeAtSample(SampleIndex sampleOffset) {
    auto msOffset = this->sampstoms(sampleOffset);
    return this->globaltransport_getBeatTime(this->getEngine()->getCurrentTime() + msOffset);
}

array<number, 2> globaltransport_getTimeSignature(MillisecondTime time) {
    number i = 3;

    while (i < this->globaltransport_timeSignatureChanges->length && this->globaltransport_timeSignatureChanges[(Index)(i + 2)] <= time) {
        i += 3;
    }

    i -= 3;

    return {
        this->globaltransport_timeSignatureChanges[(Index)i],
        this->globaltransport_timeSignatureChanges[(Index)(i + 1)]
    };
}

array<number, 2> globaltransport_getTimeSignatureAtSample(SampleIndex sampleOffset) {
    auto msOffset = this->sampstoms(sampleOffset);
    return this->globaltransport_getTimeSignature(this->getEngine()->getCurrentTime() + msOffset);
}

bool globaltransport_setTimeSignature(MillisecondTime time, number numerator, number denominator, bool notify) {
    if ((bool)(notify)) {
        this->processTimeSignatureEvent(time, (int)(numerator), (int)(denominator));
        this->globaltransport_notify = true;
    } else {
        array<number, 2> currentSig = this->globaltransport_getTimeSignature(time);

        if (currentSig[0] != numerator || currentSig[1] != denominator) {
            this->globaltransport_timeSignatureChanges->push(numerator);
            this->globaltransport_timeSignatureChanges->push(denominator);
            this->globaltransport_timeSignatureChanges->push(time);
            return true;
        }
    }

    return false;
}

void globaltransport_advance() {
    if ((bool)(this->globaltransport_tempoNeedsReset)) {
        fillSignal(this->globaltransport_tempo, this->vs, this->globaltransport_lastTempo);
        this->globaltransport_tempoNeedsReset = false;

        if ((bool)(this->globaltransport_notify)) {
            this->getEngine()->sendTempoEvent(this->globaltransport_lastTempo);
        }
    }

    if ((bool)(this->globaltransport_stateNeedsReset)) {
        fillSignal(this->globaltransport_state, this->vs, this->globaltransport_lastState);
        this->globaltransport_stateNeedsReset = false;

        if ((bool)(this->globaltransport_notify)) {
            this->getEngine()->sendTransportEvent(TransportState(this->globaltransport_lastState));
        }
    }

    if (this->globaltransport_beatTimeChanges->length > 2) {
        this->globaltransport_beatTimeChanges[0] = this->globaltransport_beatTimeChanges[(Index)(this->globaltransport_beatTimeChanges->length - 2)];
        this->globaltransport_beatTimeChanges[1] = this->globaltransport_beatTimeChanges[(Index)(this->globaltransport_beatTimeChanges->length - 1)];
        this->globaltransport_beatTimeChanges->length = 2;

        if ((bool)(this->globaltransport_notify)) {
            this->getEngine()->sendBeatTimeEvent(this->globaltransport_beatTimeChanges[0]);
        }
    }

    if (this->globaltransport_timeSignatureChanges->length > 3) {
        this->globaltransport_timeSignatureChanges[0] = this->globaltransport_timeSignatureChanges[(Index)(this->globaltransport_timeSignatureChanges->length - 3)];
        this->globaltransport_timeSignatureChanges[1] = this->globaltransport_timeSignatureChanges[(Index)(this->globaltransport_timeSignatureChanges->length - 2)];
        this->globaltransport_timeSignatureChanges[2] = this->globaltransport_timeSignatureChanges[(Index)(this->globaltransport_timeSignatureChanges->length - 1)];
        this->globaltransport_timeSignatureChanges->length = 3;

        if ((bool)(this->globaltransport_notify)) {
            this->getEngine()->sendTimeSignatureEvent(
                (int)(this->globaltransport_timeSignatureChanges[0]),
                (int)(this->globaltransport_timeSignatureChanges[1])
            );
        }
    }

    this->globaltransport_notify = false;
}

void globaltransport_dspsetup(bool force) {
    if ((bool)(this->globaltransport_setupDone) && (bool)(!(bool)(force)))
        return;

    fillSignal(this->globaltransport_tempo, this->vs, this->globaltransport_lastTempo);
    this->globaltransport_tempoNeedsReset = false;
    fillSignal(this->globaltransport_state, this->vs, this->globaltransport_lastState);
    this->globaltransport_stateNeedsReset = false;
    this->globaltransport_setupDone = true;
}

bool stackprotect_check() {
    this->stackprotect_count++;

    if (this->stackprotect_count > 128) {
        console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
        return true;
    }

    return false;
}

void updateTime(MillisecondTime time) {
    this->_currentTime = time;
    this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));

    if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
        this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;

    if (this->sampleOffsetIntoNextAudioBuffer < 0)
        this->sampleOffsetIntoNextAudioBuffer = 0;
}

void assign_defaults()
{
    unpack_01_out1 = 0;
    unpack_01_out2 = 0;
    unpack_01_out3 = 0;
    unpack_01_out4 = 0;
    unpack_01_out5 = 0;
    dspexpr_01_in1 = 0;
    dspexpr_01_in2 = 0;
    slide_tilde_01_x = 0;
    slide_tilde_01_up = 200;
    slide_tilde_01_down = 200;
    param_01_value = 0;
    cycle_tilde_01_frequency = 0;
    cycle_tilde_01_phase_offset = 0;
    dspexpr_02_in1 = 0;
    dspexpr_02_in2 = 0;
    dspexpr_03_in1 = 0;
    dspexpr_03_in2 = 0;
    cycle_tilde_02_frequency = 0;
    cycle_tilde_02_phase_offset = 0;
    slide_tilde_02_x = 0;
    slide_tilde_02_up = 200;
    slide_tilde_02_down = 200;
    param_02_value = 0;
    slide_tilde_03_x = 0;
    slide_tilde_03_up = 200;
    slide_tilde_03_down = 200;
    param_03_value = 0;
    slide_tilde_04_x = 0;
    slide_tilde_04_up = 200;
    slide_tilde_04_down = 200;
    param_04_value = 0;
    data_01_sizeout = 0;
    data_01_size = 0;
    data_01_sizems = 0;
    data_01_normalize = 0.995;
    data_01_channels = 1;
    param_05_value = 1;
    groove_01_rate_auto = 1;
    groove_01_begin = 0;
    groove_01_end = -1;
    groove_01_loop = 0;
    groove_01_crossfade = 0;
    p_01_target = 0;
    param_06_value = 0;
    lores_03_cutoff = 0;
    lores_03_resonance = 0;
    lores_03_resonance_setter(lores_03_resonance);
    midiout_01_port = 0;
    midiin_01_port = 0;
    param_07_value = 0.5;
    _currentTime = 0;
    audioProcessSampleCount = 0;
    sampleOffsetIntoNextAudioBuffer = 0;
    zeroBuffer = nullptr;
    dummyBuffer = nullptr;
    signals[0] = nullptr;
    signals[1] = nullptr;
    signals[2] = nullptr;
    signals[3] = nullptr;
    didAllocateSignals = 0;
    vs = 0;
    maxvs = 0;
    sr = 44100;
    invsr = 0.00002267573696;
    slide_tilde_01_prev = 0;
    param_01_lastValue = 0;
    cycle_tilde_01_wrap = 0;
    cycle_tilde_01_ph_currentPhase = 0;
    cycle_tilde_01_ph_conv = 0;
    cycle_tilde_01_setupDone = false;
    cycle_tilde_02_wrap = 0;
    cycle_tilde_02_ph_currentPhase = 0;
    cycle_tilde_02_ph_conv = 0;
    cycle_tilde_02_setupDone = false;
    slide_tilde_02_prev = 0;
    param_02_lastValue = 0;
    slide_tilde_03_prev = 0;
    param_03_lastValue = 0;
    slide_tilde_04_prev = 0;
    param_04_lastValue = 0;
    data_01_sizemode = 0;
    data_01_setupDone = false;
    param_05_lastValue = 0;
    groove_01_readIndex = 0;
    groove_01_playStatus = 0;
    groove_01_changeIncomingInSamples = 0;
    groove_01_incomingChange = 2;
    groove_01_crossfadeInSamples = 0;
    groove_01_setupDone = false;
    param_06_lastValue = 0;
    lores_03_setupDone = false;
    midiout_01_currentStatus = -1;
    midiout_01_status = -1;
    midiout_01_byte1 = -1;
    param_07_lastValue = 0;
    globaltransport_tempo = nullptr;
    globaltransport_tempoNeedsReset = false;
    globaltransport_lastTempo = 120;
    globaltransport_state = nullptr;
    globaltransport_stateNeedsReset = false;
    globaltransport_lastState = 0;
    globaltransport_beatTimeChanges = { 0, 0 };
    globaltransport_timeSignatureChanges = { 4, 4, 0 };
    globaltransport_notify = false;
    globaltransport_setupDone = false;
    stackprotect_count = 0;
    _voiceIndex = 0;
    _noteNumber = 0;
    isMuted = 1;
}

// member variables

    number unpack_01_out1;
    number unpack_01_out2;
    number unpack_01_out3;
    number unpack_01_out4;
    number unpack_01_out5;
    number dspexpr_01_in1;
    number dspexpr_01_in2;
    number slide_tilde_01_x;
    number slide_tilde_01_up;
    number slide_tilde_01_down;
    number param_01_value;
    number cycle_tilde_01_frequency;
    number cycle_tilde_01_phase_offset;
    number dspexpr_02_in1;
    number dspexpr_02_in2;
    number dspexpr_03_in1;
    number dspexpr_03_in2;
    number cycle_tilde_02_frequency;
    number cycle_tilde_02_phase_offset;
    number slide_tilde_02_x;
    number slide_tilde_02_up;
    number slide_tilde_02_down;
    number param_02_value;
    number slide_tilde_03_x;
    number slide_tilde_03_up;
    number slide_tilde_03_down;
    number param_03_value;
    number slide_tilde_04_x;
    number slide_tilde_04_up;
    number slide_tilde_04_down;
    number param_04_value;
    number data_01_sizeout;
    number data_01_size;
    number data_01_sizems;
    number data_01_normalize;
    number data_01_channels;
    number param_05_value;
    number groove_01_rate_auto;
    number groove_01_begin;
    number groove_01_end;
    number groove_01_loop;
    number groove_01_crossfade;
    number p_01_target;
    number param_06_value;
    number lores_03_cutoff;
    number lores_03_resonance;
    number midiout_01_port;
    number midiin_01_port;
    list message_01_set;
    number param_07_value;
    MillisecondTime _currentTime;
    SampleIndex audioProcessSampleCount;
    SampleIndex sampleOffsetIntoNextAudioBuffer;
    signal zeroBuffer;
    signal dummyBuffer;
    SampleValue * signals[4];
    bool didAllocateSignals;
    Index vs;
    Index maxvs;
    number sr;
    number invsr;
    number slide_tilde_01_prev;
    number param_01_lastValue;
    Float64BufferRef cycle_tilde_01_buffer;
    long cycle_tilde_01_wrap;
    uint32_t cycle_tilde_01_phasei;
    SampleValue cycle_tilde_01_f2i;
    number cycle_tilde_01_ph_currentPhase;
    number cycle_tilde_01_ph_conv;
    bool cycle_tilde_01_setupDone;
    Float64BufferRef cycle_tilde_02_buffer;
    long cycle_tilde_02_wrap;
    uint32_t cycle_tilde_02_phasei;
    SampleValue cycle_tilde_02_f2i;
    number cycle_tilde_02_ph_currentPhase;
    number cycle_tilde_02_ph_conv;
    bool cycle_tilde_02_setupDone;
    number slide_tilde_02_prev;
    number param_02_lastValue;
    number slide_tilde_03_prev;
    number param_03_lastValue;
    number slide_tilde_04_prev;
    number param_04_lastValue;
    Float32BufferRef data_01_buffer;
    Int data_01_sizemode;
    bool data_01_setupDone;
    number param_05_lastValue;
    Float32BufferRef groove_01_buffer;
    number groove_01_readIndex;
    Index groove_01_playStatus;
    SampleIndex groove_01_changeIncomingInSamples;
    Int groove_01_incomingChange;
    SampleIndex groove_01_crossfadeInSamples;
    bool groove_01_setupDone;
    number param_06_lastValue;
    number lores_03_b_0;
    number lores_03_a_1;
    number lores_03_a_2;
    number lores_03_x_0;
    number lores_03_y_1;
    number lores_03_y_2;
    number lores_03_last_resonance;
    number lores_03_last_frequency;
    number lores_03_last_res_calc;
    number lores_03_last_freq_calc;
    bool lores_03_setupDone;
    int midiout_01_currentStatus;
    int midiout_01_status;
    int midiout_01_byte1;
    list midiout_01_sysex;
    number param_07_lastValue;
    signal globaltransport_tempo;
    bool globaltransport_tempoNeedsReset;
    number globaltransport_lastTempo;
    signal globaltransport_state;
    bool globaltransport_stateNeedsReset;
    number globaltransport_lastState;
    list globaltransport_beatTimeChanges;
    list globaltransport_timeSignatureChanges;
    bool globaltransport_notify;
    bool globaltransport_setupDone;
    number stackprotect_count;
    DataRef RNBODefaultSinus;
    DataRef rnbuff1;
    Index _voiceIndex;
    Int _noteNumber;
    Index isMuted;
    indexlist paramInitIndices;
    indexlist paramInitOrder;
    RNBOSubpatcher_84* p_01;

};

PatcherInterface* creaternbomatic()
{
    return new rnbomatic();
}

#ifndef RNBO_NO_PATCHERFACTORY

extern "C" PatcherFactoryFunctionPtr GetPatcherFactoryFunction(PlatformInterface* platformInterface)
#else

extern "C" PatcherFactoryFunctionPtr rnbomaticFactoryFunction(PlatformInterface* platformInterface)
#endif

{
    Platform::set(platformInterface);
    return creaternbomatic;
}

} // end RNBO namespace


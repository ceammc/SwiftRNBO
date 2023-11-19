{
	"patcher" : 	{
		"fileversion" : 1,
		"appversion" : 		{
			"major" : 8,
			"minor" : 5,
			"revision" : 6,
			"architecture" : "x64",
			"modernui" : 1
		}
,
		"classnamespace" : "box",
		"rect" : [ 1394.0, 331.0, 640.0, 480.0 ],
		"bglocked" : 0,
		"openinpresentation" : 0,
		"default_fontsize" : 12.0,
		"default_fontface" : 0,
		"default_fontname" : "Arial",
		"gridonopen" : 1,
		"gridsize" : [ 15.0, 15.0 ],
		"gridsnaponopen" : 1,
		"objectsnaponopen" : 1,
		"statusbarvisible" : 2,
		"toolbarvisible" : 1,
		"lefttoolbarpinned" : 0,
		"toptoolbarpinned" : 0,
		"righttoolbarpinned" : 0,
		"bottomtoolbarpinned" : 0,
		"toolbars_unpinned_last_save" : 0,
		"tallnewobj" : 0,
		"boxanimatetime" : 200,
		"enablehscroll" : 1,
		"enablevscroll" : 1,
		"devicewidth" : 0.0,
		"description" : "",
		"digest" : "",
		"tags" : "",
		"style" : "",
		"subpatcher_template" : "",
		"assistshowspatchername" : 0,
		"boxes" : [ 			{
				"box" : 				{
					"autosave" : 1,
					"id" : "obj-3",
					"inletInfo" : 					{
						"IOInfo" : [ 							{
								"type" : "signal",
								"index" : 1,
								"tag" : "in1",
								"comment" : ""
							}
, 							{
								"type" : "signal",
								"index" : 2,
								"tag" : "in2",
								"comment" : ""
							}
, 							{
								"type" : "midi",
								"index" : -1,
								"tag" : "",
								"comment" : ""
							}
 ]
					}
,
					"maxclass" : "newobj",
					"numinlets" : 3,
					"numoutlets" : 4,
					"outletInfo" : 					{
						"IOInfo" : [ 							{
								"type" : "signal",
								"index" : 1,
								"tag" : "out1",
								"comment" : ""
							}
, 							{
								"type" : "signal",
								"index" : 2,
								"tag" : "out2",
								"comment" : ""
							}
, 							{
								"type" : "midi",
								"index" : -1,
								"tag" : "",
								"comment" : ""
							}
 ]
					}
,
					"outlettype" : [ "signal", "signal", "int", "list" ],
					"patching_rect" : [ 160.0, 151.0, 122.0, 22.0 ],
					"rnboattrcache" : 					{
						"freq1" : 						{
							"label" : "freq1",
							"isEnum" : 0,
							"parsestring" : ""
						}
,
						"freq2" : 						{
							"label" : "freq2",
							"isEnum" : 0,
							"parsestring" : ""
						}
,
						"vol1" : 						{
							"label" : "vol1",
							"isEnum" : 0,
							"parsestring" : ""
						}
,
						"vol2" : 						{
							"label" : "vol2",
							"isEnum" : 0,
							"parsestring" : ""
						}
,
						"play" : 						{
							"label" : "play",
							"isEnum" : 0,
							"parsestring" : ""
						}
,
						"cutoff" : 						{
							"label" : "cutoff",
							"isEnum" : 0,
							"parsestring" : ""
						}
,
						"resonance" : 						{
							"label" : "resonance",
							"isEnum" : 0,
							"parsestring" : ""
						}

					}
,
					"rnboversion" : "1.2.2",
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_invisible" : 1,
							"parameter_longname" : "rnbo~[1]",
							"parameter_shortname" : "rnbo~[1]",
							"parameter_type" : 3
						}

					}
,
					"saved_object_attributes" : 					{
						"optimization" : "O1",
						"parameter_enable" : 1,
						"uuid" : "61c0e9cd-866a-11ee-a9cd-52a3029e83da"
					}
,
					"snapshot" : 					{
						"filetype" : "C74Snapshot",
						"version" : 2,
						"minorversion" : 0,
						"name" : "snapshotlist",
						"origin" : "rnbo~",
						"type" : "list",
						"subtype" : "Undefined",
						"embed" : 1,
						"snapshot" : 						{
							"cutoff" : 							{
								"value" : 0.0
							}
,
							"resonance" : 							{
								"value" : 0.5
							}
,
							"vol1" : 							{
								"value" : 0.0
							}
,
							"__sps" : 							{
								"filters" : 								{

								}

							}
,
							"play" : 							{
								"value" : 1.0
							}
,
							"freq2" : 							{
								"value" : 220.0
							}
,
							"__presetid" : "swiftRnbo_test",
							"vol2" : 							{
								"value" : 0.0
							}
,
							"freq1" : 							{
								"value" : 220.0
							}

						}
,
						"snapshotlist" : 						{
							"current_snapshot" : 0,
							"entries" : [ 								{
									"filetype" : "C74Snapshot",
									"version" : 2,
									"minorversion" : 0,
									"name" : "swiftRnbo_test",
									"origin" : "swiftRnbo_test",
									"type" : "rnbo",
									"subtype" : "",
									"embed" : 0,
									"snapshot" : 									{
										"cutoff" : 										{
											"value" : 0.0
										}
,
										"resonance" : 										{
											"value" : 0.5
										}
,
										"vol1" : 										{
											"value" : 0.0
										}
,
										"__sps" : 										{
											"filters" : 											{

											}

										}
,
										"play" : 										{
											"value" : 1.0
										}
,
										"freq2" : 										{
											"value" : 220.0
										}
,
										"__presetid" : "swiftRnbo_test",
										"vol2" : 										{
											"value" : 0.0
										}
,
										"freq1" : 										{
											"value" : 220.0
										}

									}
,
									"fileref" : 									{
										"name" : "swiftRnbo_test",
										"filename" : "swiftRnbo_test.maxsnap",
										"filepath" : "~/Documents/Max 8/Snapshots",
										"filepos" : -1,
										"snapshotfileid" : "c579b2ab9029f41d91d53e4b85bba1ee"
									}

								}
 ]
						}

					}
,
					"text" : "rnbo~ swiftRnbo_test",
					"varname" : "rnbo~[1]"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-2",
					"maxclass" : "ezdac~",
					"numinlets" : 2,
					"numoutlets" : 0,
					"patching_rect" : [ 160.0, 231.0, 45.0, 45.0 ]
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"destination" : [ "obj-2", 1 ],
					"source" : [ "obj-3", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-2", 0 ],
					"source" : [ "obj-3", 0 ]
				}

			}
 ],
		"parameters" : 		{
			"obj-3" : [ "rnbo~[1]", "rnbo~[1]", 0 ],
			"parameterbanks" : 			{
				"0" : 				{
					"index" : 0,
					"name" : "",
					"parameters" : [ "-", "-", "-", "-", "-", "-", "-", "-" ]
				}

			}
,
			"inherited_shortname" : 1
		}
,
		"dependency_cache" : [ 			{
				"name" : "SwiftRNBO_Example.maxsnap",
				"bootpath" : "~/Documents/Max 8/Snapshots",
				"patcherrelativepath" : "../../../../Max 8/Snapshots",
				"type" : "mx@s",
				"implicit" : 1
			}
, 			{
				"name" : "SwiftRNBO_Example[1].maxsnap",
				"bootpath" : "~/Documents/Max 8/Snapshots",
				"patcherrelativepath" : "../../../../Max 8/Snapshots",
				"type" : "mx@s",
				"implicit" : 1
			}
, 			{
				"name" : "cherokee.aif",
				"bootpath" : "C74:/media/msp",
				"type" : "AIFF",
				"implicit" : 1
			}
, 			{
				"name" : "swiftRnbo_test.maxsnap",
				"bootpath" : "~/Documents/Max 8/Snapshots",
				"patcherrelativepath" : "../../../../Max 8/Snapshots",
				"type" : "mx@s",
				"implicit" : 1
			}
, 			{
				"name" : "swiftRnbo_test.rnbopat",
				"bootpath" : "~/Documents/Personal/Projects/SwiftRNBO-eldarsadykov/SwiftRNBO",
				"patcherrelativepath" : ".",
				"type" : "RBOP",
				"implicit" : 1
			}
 ],
		"autosave" : 0,
		"snapshot" : 		{
			"filetype" : "C74Snapshot",
			"version" : 2,
			"minorversion" : 0,
			"name" : "snapshotlist",
			"origin" : "jpatcher",
			"type" : "list",
			"subtype" : "Undefined",
			"embed" : 1,
			"snapshot" : 			{
				"valuedictionary" : 				{
					"parameter_values" : 					{
						"blob" : 						{
							"rnbo~" : [ 								{
									"filetype" : "C74Snapshot",
									"version" : 2,
									"minorversion" : 0,
									"name" : "untitled",
									"origin" : "b478a66d-ab11-11ed-a66d-a64a47a292b2",
									"type" : "rnbo",
									"subtype" : "",
									"embed" : 1,
									"snapshot" : 									{
										"cutoff" : 										{
											"value" : 0.0
										}
,
										"resonance" : 										{
											"value" : 0.5
										}
,
										"vol1" : 										{
											"value" : 0.0
										}
,
										"__sps" : 										{
											"filters" : 											{

											}

										}
,
										"play" : 										{
											"value" : 1.0
										}
,
										"freq2" : 										{
											"value" : 220.0
										}
,
										"__presetid" : "b478a66d-ab11-11ed-a66d-a64a47a292b2",
										"vol2" : 										{
											"value" : 0.0
										}
,
										"freq1" : 										{
											"value" : 220.0
										}

									}

								}
 ]
						}

					}

				}

			}
,
			"snapshotlist" : 			{
				"current_snapshot" : 0,
				"entries" : [ 					{
						"filetype" : "C74Snapshot",
						"version" : 2,
						"minorversion" : 0,
						"name" : "SwiftRNBO_Example",
						"origin" : "SwiftRNBO_Example",
						"type" : "patcher",
						"subtype" : "Undefined",
						"embed" : 0,
						"fileref" : 						{
							"name" : "SwiftRNBO_Example",
							"filename" : "SwiftRNBO_Example.maxsnap",
							"filepath" : "~/Documents/Max 8/Snapshots",
							"filepos" : -1,
							"snapshotfileid" : "4d651552a17a01c2aeafc8eb9bb886b5"
						}

					}
, 					{
						"filetype" : "C74Snapshot",
						"version" : 2,
						"minorversion" : 0,
						"name" : "SwiftRNBO_Example[1]",
						"origin" : "SwiftRNBO_Example",
						"type" : "patcher",
						"subtype" : "Undefined",
						"embed" : 0,
						"snapshot" : 						{
							"valuedictionary" : 							{
								"parameter_values" : 								{
									"blob" : 									{
										"rnbo~" : [ 											{
												"filetype" : "C74Snapshot",
												"version" : 2,
												"minorversion" : 0,
												"name" : "untitled",
												"origin" : "b478a66d-ab11-11ed-a66d-a64a47a292b2",
												"type" : "rnbo",
												"subtype" : "",
												"embed" : 1,
												"snapshot" : 												{
													"cutoff" : 													{
														"value" : 0.0
													}
,
													"resonance" : 													{
														"value" : 0.5
													}
,
													"vol1" : 													{
														"value" : 0.0
													}
,
													"__sps" : 													{
														"filters" : 														{

														}

													}
,
													"play" : 													{
														"value" : 1.0
													}
,
													"freq2" : 													{
														"value" : 220.0
													}
,
													"__presetid" : "b478a66d-ab11-11ed-a66d-a64a47a292b2",
													"vol2" : 													{
														"value" : 0.0
													}
,
													"freq1" : 													{
														"value" : 220.0
													}

												}

											}
 ]
									}

								}

							}

						}
,
						"fileref" : 						{
							"name" : "SwiftRNBO_Example[1]",
							"filename" : "SwiftRNBO_Example[1].maxsnap",
							"filepath" : "~/Documents/Max 8/Snapshots",
							"filepos" : -1,
							"snapshotfileid" : "6754ecb6282afaed1988690f440ad080"
						}

					}
 ]
			}

		}

	}

}

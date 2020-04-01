#pragma once

// Need to handle patches better.
#define UNITYENGINE_GETDELTATIME_ADDR              0x00000001809461F0
#define UNITYENGINE_GETDELTATIME_NEWPATCH_ADDR     0x00000001809465F0
#define UNITYENGINE_GETDELTATIME_NEWPATCH_RVA      0x9465F0

// qword ptr[00000001815EEE50 <unityplayer.&il2cpp_runtime_invoke>] = <gameassembly.il2cpp_runtime_invoke>
#define IL2CPP_RUNTIME_INVOKE_IAT_ADDR             0x00000001815EEE50                                                                                                  |
#define IL2CPP_RUNTIME_INVOKE_IAT_NEWPATCH_ADDR    0x00000001815EFE40
#define IL2CPP_RUNTIME_INVOKE_IAT_NEWPATCH_RVA     0x15EFE40

#define UNITYENGINE_PLAYERLOOPINTERNAL_ADDR          0x00000001805ECE80
#define UNITYENGINE_PLAYERLOOPINTERNAL_NEWPATCH_ADDR 0x00000001805ED7A0
#define UNITYENGINE_PLAYERLOOPINTERNAL_NEWPATCH_RVA  0x5ED7A0

//qword ptr [000000000905F5F8 <gameassembly.&XInputGetState>]=<xinput9_1_0.XInputGetState>
//qword ptr [000000000905F5F8 <gameassembly.&XInputGetState>]=<xinput9_1_0.XInputGetState>
#define XINPUT_GETSTATE_IAT_ADDR            0x00000000091AF5F8

#define COMPOUNDBUTTONINPUT_GETBUTTON_RVA   0xFC4810

// ?? update this
#define COMPOUNDBUTTONINPUT_GETBUTTON_NEWPATCH_RVA 0x000000

#define INPUTBUTTONPROCESSOR_GETBUTTON_RVA  0xBC73D0
#define INPUTBUTTONPROCESSOR_GETBUTTON_NEWPATCH_RVA 0xBDC050

#define INPUTBUTTONPROCESSOR_GETCOMMAND_RVA 0xBC77F0
#define INPUTBUTTONPROCESSOR_GETCOMMAND_NEWPATCH_RVA 0xBDC470

#define UNITYENGINE_GETMOUSEPOSITION_INJECTED_ADDR 0x0000000180928CC0
#define UNITYENGINE_GETMOUSEPOSITION_INJECTED_RVA 0x928CC0

//00000001809499E0
#define UNITYENGINE_SCREENTOVIEWPORTPOINTINJECTED_ADDR     0x00000001809499E0
#define UNITYENGINE_SCREENTOVIEWPORTPOINTINJECTED_NEWPATCH_ADDR 0x0000000180949DE0
#define UNITYENGINE_SCREENTOVIEWPORTPOINTINJECTED_NEWPATCH_RVA  0x949DE0

//0000000180636553 | 48:8D0D A620EC00                        | lea rcx,qword ptr ds:[1814F8600]                                                                                                   |
#define UNITYENGINE_INDEXER_PTR_ADDR               0x00000001814F8600
#define UNITYENGINE_INDEXER_PTR_NEWPATCH_ADDR      0x00000001814F9610
#define UNITYENGINE_INDEXER_PTR_RVA                0x14F9610

// this shouldn't have changed
#define UNITYENGINE_INPUT_INDEX                    0x01
#define UNITYENGINE_PHYSICS_INDEX                  0x07

#define CHARACTERS_GETSEIN_NEWPATCH_RVA            0x50E670

#define SEINCHARACTER_GETPOSITION_NEWPATCH_RVA     0xA65B20
#define SEINCHARACTER_SETPOSITION_NEWPATCH_RVA     0xA65B80
#define SEINCHARACTER_GETLOCALSPEED_NEWPATCH_RVA   0xA68C50
#define CHARPLATFORMMOVEMENT_GETRIGIDBODYVELOCITY_NEWPATCH_RVA 0xB99D20

// this + 0x65 for GameSetting instance
#define PLAYERINPUT_GETWASKEYBOARDUSEDLAST_NEWPATCH_RVA  0x12F9030

#define UNITYENGINE_SETTIMESCALE_NEWPATCH_ADDR 0x00000001809469B0
#define UNITYENGINE_SETTIMESCALE_NEWPATCH_RVA  0x9469B0

#define UNKNOWN_FUNCTION_OFFSETFORQUALITYSETTINGS_NEWPATCH_RVA 0x869A50

#define UNITYENGINE_SETVSYNCCOUNT_NEWPATCH_ADDR   0x0000000180936C40
#define UNITYENGINE_SETVSYNCCOUNT_NEWPATCH_RVA    0x936C40

//00000001808106D0 | 890D CEDDC800 | mov dword ptr ds : [18149E4A4], ecx |
#define UNITYENGINE_TARGETFRAMERATE_NEWPATCH_ADDR 0x000000018149E4A4
#define UNITYENGINE_TARGETFRAMERATE_NEWPATCH_RVA  0x149E4A4

#define UNITYENGINE_SETMAXIMUMDELTATIME_NEWPATCH_ADDR 0x0000000180946950
#define UNITYENGINE_SETMAXIMUMDELTATIME_NEWPATCH_RVA  0x946950


#define GAMEASSEMBLY_MAXTIMESTEP_SETCALL_NEWPATCH_RVA 0x143A0C4
/*
 * If not stated otherwise in this file or this component's Licenses.txt file the
 * following copyright and licenses apply:
 *
 * Copyright 2016 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/
#ifndef _MESSAGESENDER_H_
#define _MESSAGESENDER_H_

#include "RDKIrKeyCodes.h"

typedef struct
{
	char* comamnd;
	int keyCode;
} lookUpTable;

#ifdef _SKQ_KEY_MAP_1_
lookUpTable table[] =
{
{ "power", KED_TVPOWER },
{ "home", KED_MENU }, 
{ "guide", KED_GUIDE }, //Same as KED_MENU
{ "sky", KED_STAR },  

{ "0", KED_DIGIT0 },
{ "1", KED_DIGIT1 },
{ "2", KED_DIGIT2 },
{ "3", KED_DIGIT3 },
{ "4", KED_DIGIT4 },
{ "5", KED_DIGIT5 },
{ "6", KED_DIGIT6 },
{ "7", KED_DIGIT7 },
{ "8", KED_DIGIT8 },
{ "9", KED_DIGIT9 },

{ "up", KED_ARROWUP },
{ "chup", KED_CHANNELUP },
{ "down", KED_ARROWDOWN },
{ "chdown", KED_CHANNELUP },
{ "left", KED_ARROWLEFT },
{ "right", KED_ARROWRIGHT },
{ "enter", KED_SELECT },

{ "mute", KED_MUTE },
{ "volup", KED_VOLUMEUP },
{ "voldown", KED_VOLUMEDOWN },
{ "pageup", KED_PAGEUP },
{ "pagedown", KED_PAGEDOWN },

{ "play", KED_PLAY },
{ "pause", KED_PAUSE },
{ "fastfwd", KED_FASTFORWARD },
{ "rewind", KED_REWIND },

{ "exit", KED_EXIT },
{ "search", KED_SEARCH }, 
{ "record", KED_RECORD },

{ "info", KED_INFO },

{ "red", KED_KEYC }, 
{ "green", KED_KEYD }, 
{ "yellow", KED_KEYA }, 
{ "blue", KED_KEYB }, 

{ "apps", KED_PERIOD }, 
{ "ondemand", KED_ONDEMAND }, //Same as KED_PERIOD
{ "help", KED_HELP },

{ "inputkey", KED_INPUTKEY },
{ "lowBat", KED_POUND } 

};

//Scancode Mapping
typedef struct {
	int iKeyCode;
    int iScanCode;
} Sky_keycodeMap;

static Sky_keycodeMap kSkyKeycodeMapTable [] =
{
	{KED_TVPOWER, 0x0C},
	{KED_MENU, 0xCC},
	{KED_GUIDE, 0xCC},
	{KED_STAR, 0x80},

	{KED_DIGIT1, 0x01},
	{KED_DIGIT2, 0x02},
	{KED_DIGIT3, 0x03},
	{KED_DIGIT4, 0x04},
	{KED_DIGIT5, 0x05},
	{KED_DIGIT6, 0x06},
	{KED_DIGIT7, 0x07},
	{KED_DIGIT8, 0x08},
	{KED_DIGIT9, 0x09},
	{KED_DIGIT0, 0x00},
				  
	{KED_ARROWUP, 0x58},
	{KED_CHANNELUP, 0x58},
	{KED_ARROWDOWN, 0x59},
	{KED_CHANNELDOWN, 0x59},
	{KED_ARROWLEFT, 0x5A},
	{KED_ARROWRIGHT, 0x5B},
	{KED_SELECT, 0x5C},
				  
	{KED_MUTE, 0x0D},
	{KED_VOLUMEUP, 0x10},
	{KED_VOLUMEDOWN, 0x11},
	{KED_PAGEUP, 0x20},
	{KED_PAGEDOWN, 0x21},
				  
	{KED_PLAY, 0x3E},
	{KED_PAUSE, 0x3E},
	{KED_FASTFORWARD, 0x28},
	{KED_REWIND, 0x3D},
				  
	{KED_EXIT, 0x83},
	{KED_SEARCH, 0x7E},
	{KED_RECORD, 0x40},
				  
	{KED_INFO, 0xCB},
				  
	{KED_KEYC, 0x6D},
	{KED_KEYD, 0x6E},
	{KED_KEYA, 0x6F},
	{KED_KEYB, 0x70},
				  
	{KED_PERIOD, 0xF5},
	{KED_ONDEMAND, 0xF5},
	{KED_HELP, 0x81},
				  
	{KED_INPUTKEY, 0x29},
	{KED_POUND, 0x47}
};


#else //else _SKQ_KEY_MAP_1_
lookUpTable table[] =
{
{ "0", KED_DIGIT0 },
{ "1", KED_DIGIT1 },
{ "2", KED_DIGIT2 },
{ "3", KED_DIGIT3 },
{ "4", KED_DIGIT4 },
{ "5", KED_DIGIT5 },
{ "6", KED_DIGIT6 },
{ "7", KED_DIGIT7 },
{ "8", KED_DIGIT8 },
{ "9", KED_DIGIT9 },
{ "power", KED_POWER },
{ "allpower", KED_RF_POWER },
{ "up", KED_ARROWUP },
{ "down", KED_ARROWDOWN },
{ "left", KED_ARROWLEFT },
{ "right", KED_ARROWRIGHT },
{ "select", KED_SELECT },
{ "enter", KED_ENTER },
{ "exit", KED_EXIT },
{ "chup", KED_CHANNELUP },
{ "chdown", KED_CHANNELDOWN },
{ "volup", KED_VOLUMEUP },
{ "voldown", KED_VOLUMEDOWN },
{ "mute", KED_MUTE },
{ "guide", KED_GUIDE },
{ "viewingguide", KED_VIEWINGGUIDE },
{ "info", KED_INFO },
{ "settings", KED_SETTINGS },
{ "pageup", KED_PAGEUP },
{ "pagedown", KED_PAGEDOWN },
{ "favourite", KED_FAVORITE },
{ "rewind", KED_REWIND },
//{ "forward", KED_FASTFORWARD },
{ "fastfwd", KED_FASTFORWARD },
{ "play", KED_PLAY },
{ "stop", KED_STOP },
{ "pause", KED_PAUSE },
{ "record", KED_RECORD },
{ "bypass", KED_BYPASS },
{ "tvvcr", KED_TVVCR },
{ "replay", KED_REPLAY },
{ "help", KED_HELP },
{ "recallfavorite", KED_RECALL_FAVORITE_0 },
{ "clear", KED_CLEAR },
{ "delete", KED_DELETE },
{ "start", KED_START },
{ "pound", KED_POUND },
{ "frontpanel1", KED_FRONTPANEL1 },
{ "frontpanel2", KED_FRONTPANEL2 },
{ "ok", KED_OK },
{ "star", KED_STAR },
{ "tvpower", KED_TVPOWER },
{ "previous", KED_PREVIOUS },
{ "next", KED_NEXT },
{ "menu", KED_MENU },
{ "inputkey", KED_INPUTKEY },
{ "livetv", KED_LIVE },
{ "mydvr", KED_MYDVR },
{ "ondemand", KED_ONDEMAND },
{ "stbmenu", KED_STB_MENU },
{ "audio", KED_AUDIO },
{ "factory", KED_FACTORY },
{ "rfenable", KED_RFENABLE },
{ "list", KED_LIST },
{ "undefindedkey", KED_UNDEFINEDKEY },
{ "back", KED_BACK },
{ "swap", KED_DISPLAY_SWAP },
{ "pipmove", KED_PINP_MOVE },
{ "piptoggle", KED_PINP_TOGGLE },
{ "pipchdown", KED_PINP_CHDOWN },
{ "pipchup", KED_PINP_CHUP },
{ "activate", KED_DMC_ACTIVATE },
{ "deactivate", KED_DMC_DEACTIVATE },
{ "dmcquery", KED_DMC_QUERY },
{ "otrstart", KED_OTR_START },
{ "strstop", KED_OTR_STOP }
//{ "skip", KED_ }
//{ "dvdmenu", KED_ }
//{ "tvjump", KED_ }
//{ "mytv", KED_ }
//{ "mymusic", KED_ }
//{ "rectv", KED_ }
//{ "mypictures", KED_ }
//{ "myvideos", KED_ }
//{ "dvdangle", KED_ }
//{ "dvdaudio", KED_ }
//{ "dvdsubtitles", KED_ }
//{ "OEM1", KED_ }
//{ "OEM2", KED_ }
//{ "internet", KED_ }
//{ "email", KED_ }
//{ "search", KED_ }
//{ "wake", KED_ }
//{ "calculator", KED_ }
//{ "camera", KED_ }
//{ "zoomin", KED_ }
//{ "zoomout", KED_ }
//{ "document", KED_ }
//{ "music", KED_ }
//{ "mouseleftbtn", KED_ }
//{ "mouserightbtn", KED_ }
//{ "home", KED_ }
//{ "nokey", KED_ }
//{ "bkspace", KED_ }
//{ "bkspace", KED_ }
//{ "F1", KED_ }
//{ "F2", KED_ }
//{ "F3", KED_ }
//{ "F4", KED_ }
//{ "period", KED_ }
//{ "eject", KED_ }
//{ "fewskip", KED_ }
//{ "revskip", KED_ }
//{ "source", KED_ }
//{ "setup", KED_ }
//{ "keyboard", KED_ }
//{ "sleep", KED_ }
//{ "closedcaption", KED_ }
//{ "network", KED_ }
//{ "subaudio", KED_ }
//{ "subtitle", KED_ }
//{ "audiotrack", KED_ }
//{ "dvdtopmenu", KED_ }
//{ "dvdresume", KED_ }
//{ "button_a", KED_ }
//{ "button_b", KED_ }
//{ "button_c", KED_ }
//{ "button_d", KED_ }
//{ "language", KED_ }
//{ "hdzoom", KED_ }
//{ "recall", KED_ }
//{ "lock", KED_ }
//{ "navprev", KED_ }
//{ "navnext", KED_ }
//{ "voloptmz", KED_ }
//{ "frontpanel3", KED_ }
};
#endif //end _SKQ_KEY_MAP_1_


#define IARM_BUS_UIEVENTSIMULATOR_NAME                                             "UIEventSimulator" /*!<  UIEventSimulator -bus name */

typedef enum _UIEventSimulator_EventId_t {
	IARM_BUS_UIEVENTSIMULATOR_UIDEV_EVENT_IRKEY,
	IARM_BUS_UIEVENTSIMULATOR_EVENT_MAX
}IARM_Bus_UIEVENTSIMULATOR_EventId_t;

/*typedef struct _UIEventSimulator_EventData_t
{
	int id;
	union {
	struct _IRKEY_DATA{
		int keyType;              !< Key type (UP/DOWN/REPEAT) 
		int keyCode;              !< Key code  
        } irkey, fpkey;
    } data;

}IARM_Bus_UIEventSimulator_EventData_t;*/



#endif

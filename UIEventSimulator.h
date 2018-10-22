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

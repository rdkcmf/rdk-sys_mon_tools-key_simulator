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
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "libIBus.h"
#include "UIEventSimulator.h"
#include "libIARM.h"
#include "irMgr.h"

//#define TRACE

IARM_Result_t UIEventSimulator_Start();
IARM_Result_t findKeyCode(char command[]);
IARM_Result_t sendCommand();
void sendKeyEventToIARM(int keyType, int keyCode);
void usage(void);

IARM_Result_t UIEventSimulator_Stop(void);
char* executableName;

static int keyCode = -1;
static int interval = 1;
static int repeat = 1;

/**
 * @brief main!
 */
int main(int argc, char *argv[])
{
#ifdef TRACE
	printf("[FUNC] %s [LINE] %d\n", __FUNCTION__, __LINE__);
#endif

	if (UIEventSimulator_Start() != IARM_RESULT_SUCCESS)
	{
		return 0;
	}

	printf("\n\nProgram name: %s\n", argv[0]);
	executableName = argv[0];

	while ((argc > 1) && (argv[1][0] == '-'))
	{
		switch (argv[1][1])
		{
		case 'h':
		case 'H':
			usage();
			break;

		case 'r':
		case 'R':
			printf("Repeat = %s\n", &argv[1][2]);
			repeat = atoi(&argv[1][2]);
			break;

		case 'i':
		case 'I':
			printf("Interval = %s\n", &argv[1][2]);
			interval = atoi(&argv[1][2]);
			break;

		case 'k':
		case 'K':
			printf("Command = %s\n", &argv[1][2]);
			if (findKeyCode(&argv[1][2]) != IARM_RESULT_SUCCESS)
			{
				printf("Key code not found %s Exit %s\n", &argv[1][2], argv[0]);
				return 0; // get out!!!
			}
			break;

		default:
			printf("Wrong Arguments %s\n", argv[1]);
			break;

		}
		++argv;
		--argc;
	}

	if (keyCode >= 0)
	{
		sendCommand();
	}
	UIEventSimulator_Stop();
	return 0;
}

/**
 * @brief Initialize the IARM.
 *
 * @return IARM_Result_t Error Code.
 */
IARM_Result_t UIEventSimulator_Start()
{
#ifdef TRACE
	printf("[FUNC] %s [LINE] %d\n", __FUNCTION__, __LINE__);
#endif
	IARM_Bus_Init(IARM_BUS_UIEVENTSIMULATOR_NAME);
	IARM_Bus_Connect();
	return IARM_RESULT_SUCCESS;
}

/**
 * @brief Given a string find the key code (KED_*)
 *
 * @param [in] the command to find.
 *
 * @return IARM_Result_t Error Code.
 */
IARM_Result_t findKeyCode(char command[])
{
	IARM_Result_t result = IARM_RESULT_INVALID_PARAM;
	int index = 0;

#ifdef TRACE
	printf("[FUNC] %s [LINE] %d\n", __FUNCTION__, __LINE__);
#endif

	int length = ((sizeof table) / sizeof table[0]);

	for (index = 0; index < length; index++)
	{
		if (strcmp(command, table[index].comamnd) == 0)
		{
			keyCode = table[index].keyCode;
			printf("Found %s keycode = %d\n", command, keyCode);
			result = IARM_RESULT_SUCCESS;
		}
	}

	return result;
}

/**
 * @brief Wrapper to send the command to IARM.  Repeat and interval will be evaluated and executed.
 *
 * @return IARM_Result_t Error Code.
 */

IARM_Result_t sendCommand()
{
	int i;

#ifdef TRACE
	printf("[FUNC] %s [LINE] %d\n", __FUNCTION__, __LINE__);
	printf("[FUNC] %s Command=%d repeat=%d interval=%d\n", __FUNCTION__, keyCode, repeat, interval);
#endif

	for (i = 0; i < repeat; i++)
	{
		sendKeyEventToIARM(KET_KEYDOWN, keyCode);
		usleep(100);
		sendKeyEventToIARM(KET_KEYUP, keyCode);
		sleep(interval);
	}

	return IARM_RESULT_SUCCESS;
}

/**
 * @brief send the key type and key code to IARM
 *
 */
void sendKeyEventToIARM(int keyType, int keyCode)
{
	
#ifdef TRACE
	printf("[FUNC] %s [LINE] %d\n", __FUNCTION__, __LINE__);
#endif

	printf("Sending Key (%x, %x) from %s\r\n", keyType, keyCode, executableName);
	IARM_Bus_IRMgr_EventData_t eventData;
        eventData.data.irkey.keyType = keyType;
        eventData.data.irkey.keyCode = keyCode;
        eventData.data.irkey.isFP = 0;
        IARM_Bus_BroadcastEvent(IARM_BUS_IRMGR_NAME, (IARM_EventId_t) IARM_BUS_IRMGR_EVENT_IRKEY, (void *)&eventData, sizeof(eventData));
}

/**
 * @brief print the program usage.
 *
 */
void usage(void)
{
	int index = 0;
	int length = ((sizeof table) / sizeof table[0]);

#ifdef TRACE
	printf("[FUNC] %s [LINE] %d\n", __FUNCTION__, __LINE__);
#endif

	printf("--------------------------------------------------\n");
	printf("--------------------------------------------------\n");
	printf("---                                            ---\n");
	printf("--                                              --\n");
	printf("-                                                -\n");
	printf("-h print usage\n");
	printf("-r repeat number of times command is sent (default is once)\n");
	printf("-i interval between commands (default 1 second\n");
	printf("-k command to send (see list below)\n");
	for (index = 0; index < length; index++)
	{
		printf("KeyCode = %s \n", table[index].comamnd);
	}
	printf("Example:\n");
	printf("\t %s -kexit\n", executableName);
	printf("\t %s -r3 -i2 -kmenu\n", executableName);
	printf("\t %s -r10 -i10 -kchup\n", executableName);
	printf("\t %s -kchdown -r5 \n", executableName);
	printf("-                                                -\n");
	printf("--                                              --\n");
	printf("---                                            ---\n");
	printf("--------------------------------------------------\n");
	printf("--------------------------------------------------\n");
}


IARM_Result_t UIEventSimulator_Stop(void)
{
    IARM_Bus_Disconnect();
    IARM_Bus_Term();

    return IARM_RESULT_SUCCESS;
}


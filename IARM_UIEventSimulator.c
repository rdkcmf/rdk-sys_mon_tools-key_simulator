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
#include <string.h>
#include <unistd.h>

#include "UIEventSimulator.h"
#include "libCMAF.h"
#include "uidev.h"

//#define TRACE

CMAF_Result_t initCMAF();
CMAF_Result_t findKeyCode(char command[]);
CMAF_Result_t sendCommand();
void sendKeyEventToCMAF(int keyType, int keyCode);
void usage(void);

char* executableName;
char* programName = "UIEventSimulator";

static void *m_grpCtx = NULL;
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

	if (initCMAF() != CMAF_RESULT_SUCCESS)
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
			if (findKeyCode(&argv[1][2]) != CMAF_RESULT_SUCCESS)
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

	return 0;
}

/**
 * @brief Initialize the CMAF.
 *
 * @return CMAF_Result_t Error Code.
 */
CMAF_Result_t initCMAF()
{
#ifdef TRACE
	printf("[FUNC] %s [LINE] %d\n", __FUNCTION__, __LINE__);
#endif

	CMAF_Result_t result = CMAF_Init(UIDEV_PROCESSGROUP_NAME, programName, (void **) &m_grpCtx);

	if (result != CMAF_RESULT_SUCCESS)
	{
		printf("Error initializing CMAF_Init %s %s \n", UIDEV_PROCESSGROUP_NAME, programName);
	}

	return result;
}

/**
 * @brief Given a string find the key code (KED_*)
 *
 * @param [in] the command to find.
 *
 * @return CMAF_Result_t Error Code.
 */
CMAF_Result_t findKeyCode(char command[])
{
	CMAF_Result_t result = CMAF_RESULT_INVALID_PARAM;
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
			result = CMAF_RESULT_SUCCESS;
		}
	}

	return result;
}

/**
 * @brief Wrapper to send the command to CMAF.  Repeat and interval will be evaluated and executed.
 *
 * @return CMAF_Result_t Error Code.
 */

CMAF_Result_t sendCommand()
{
	int i;

#ifdef TRACE
	printf("[FUNC] %s [LINE] %d\n", __FUNCTION__, __LINE__);
	printf("[FUNC] %s Command=%d repeat=%d interval=%d\n", __FUNCTION__, keyCode, repeat, interval);
#endif

	for (i = 0; i < repeat; i++)
	{
		sendKeyEventToCMAF(KET_KEYDOWN, keyCode);
		usleep(100);
		sendKeyEventToCMAF(KET_KEYUP, keyCode);
		sleep(interval);
	}

	return CMAF_RESULT_SUCCESS;
}

/**
 * @brief send the key type and key code to CMAF
 *
 * @return CMAF_Result_t Error Code.
 */
void sendKeyEventToCMAF(int keyType, int keyCode)
{

#ifdef TRACE
	printf("[FUNC] %s [LINE] %d\n", __FUNCTION__, __LINE__);
#endif

	printf("Sending Key (%x, %x) from %s\r\n", keyType, keyCode, executableName);

	UIDev_EventData_t *eventData = NULL;
	CMAF_Malloc(m_grpCtx, CMAF_MEMTYPE_PROCESSSHARE, sizeof(UIDev_EventData_t), (void **) &eventData);
	eventData->id = UIDEV_EVENT_IRKEY;
	eventData->data.irkey.keyType = keyType;
	eventData->data.irkey.keyCode = keyCode;
	CMAF_NotifyEvent(m_grpCtx, (CMAF_EventId_t) UIDEV_EVENT_IRKEY, (void *) eventData);
}

/**
 * @brief print the program usage.
 *
 * @return CMAF_Result_t Error Code.
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

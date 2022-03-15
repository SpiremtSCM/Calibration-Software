/*Added by YC
For NIDAQ update*/

#include"stdafx.h"
#include"VC_Update.h"

//Constructor nil
VC_Update::VC_Update() {
}

int VC_Update::DAQ_Update(float voltage) {
	int			error = 0;
	TaskHandle	taskHandle = 0;
	char		errBuff[2048] = { '\0' };

	//set value for V
	//0 - open Q max
	//5.5 - open for 2/3
	//8 - open for 1/3
	//10 - close

	float64     data[1] = { voltage };

	/*********************************************/
	// DAQmx Configure Code
	/*********************************************/
	DAQmxErrChk(DAQmxCreateTask("", &taskHandle));
	DAQmxErrChk(DAQmxCreateAOVoltageChan(taskHandle, "Dev1/ao0", "", -10.0, 10.0, DAQmx_Val_Volts, ""));

	/*********************************************/
	// DAQmx Start Code
	/*********************************************/
	DAQmxErrChk(DAQmxStartTask(taskHandle));

	/*********************************************/
	// DAQmx Write Code
	/*********************************************/
	DAQmxErrChk(DAQmxWriteAnalogF64(taskHandle, 1, 1, 10.0, DAQmx_Val_GroupByChannel, data, NULL, NULL));

Error:
	if (DAQmxFailed(error))
		DAQmxGetExtendedErrorInfo(errBuff, 2048);
	if (taskHandle != 0) {
		/*********************************************/
		// DAQmx Stop Code
		/*********************************************/
		DAQmxStopTask(taskHandle);
		DAQmxClearTask(taskHandle);
	}
	if (DAQmxFailed(error))
		return 1;
	//getchar();
	return 0;
}
import { startTestRequested } from "./../store/slices/testSlice";
import { Port, TestStartRequest } from "../model/dataModels";
import type { Dispatch, AnyAction } from "@reduxjs/toolkit";


interface StartTestProps {
    testName: string;
    attuIp: string;
    networkPort: number;
    port: Port;
}

export const startTestWs = (
  testProps: StartTestProps,
  sendJsonMessage: (data: any) => void,
  dispatch: Dispatch<AnyAction>      
) => {
  
  const testId = crypto.randomUUID();

  const newTest: TestStartRequest = {
    testId,
    testName: testProps.testName ?? "",
    attuIp: testProps.attuIp ?? "",
    networkPort: testProps.networkPort ?? 0,
    port: testProps.port as Port,
    status: 'isRunning'
  };

  sendJsonMessage({
    packet_type: 1,
    payload: testId,
  });

  dispatch(startTestRequested(newTest));

};
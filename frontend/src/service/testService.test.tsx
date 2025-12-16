import { startTestWs } from "./testService";
import { startTestRequested } from "./../store/slices/testSlice";
import type { Port } from "../model/dataModels";
import type { Dispatch, AnyAction } from "@reduxjs/toolkit";

import { randomUUID } from "crypto";

beforeAll(() => {
  if (!globalThis.crypto) {
    globalThis.crypto = {} as Crypto;
  }
  if (!globalThis.crypto.randomUUID) {
    (globalThis.crypto as any).randomUUID = randomUUID;
  }
});

describe("startTestWs", () => {
  it("sends a start-test websocket message with the expected payload", () => {
    const uuid = "00000000-0000-0000-0000-000000000123";
    jest.spyOn(globalThis.crypto, "randomUUID").mockReturnValue(uuid);

    const sendJsonMessage = jest.fn();
    const dispatch = jest.fn() as unknown as Dispatch<AnyAction>;

    const testProps = {
      testName: "Ping Test",
      attuIp: "127.0.0.1",
      networkPort: 8080,
      port: "A" as unknown as Port,
    };

    startTestWs(testProps, sendJsonMessage, dispatch);

    expect(sendJsonMessage).toHaveBeenCalledWith({
      type: "start-test",
      payload: {
        testId: uuid,
        testName: "Ping Test",
        attuIp: "127.0.0.1",
        networkPort: 8080,
        port: testProps.port,
        status: "isRunning",
      },
    });
  });

  it("dispatches startTestRequested with the created TestStartRequest", () => {
    const uuid = "00000000-0000-0000-0000-000000000993";
    jest.spyOn(globalThis.crypto, "randomUUID").mockReturnValue(uuid);

    const sendJsonMessage = jest.fn();
    const dispatchMock = jest.fn();
    const dispatch = dispatchMock as unknown as Dispatch<AnyAction>;

    const testProps = {
      testName: "My Test",
      attuIp: "1.2.3.4",
      networkPort: 1234,
      port: "A" as unknown as Port,
    };

    startTestWs(testProps, sendJsonMessage, dispatch);

    expect(dispatchMock).toHaveBeenCalledWith(
      startTestRequested({
        testId: uuid,
        testName: "My Test",
        attuIp: "1.2.3.4",
        networkPort: 1234,
        port: testProps.port,
        status: "isRunning",
      } as any)
    );
  });
});

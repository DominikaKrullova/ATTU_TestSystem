import reducer, { startTestRequested, setTestResults, removeTest } from "./testSlice";
import type { Test, TestResponse } from "../../model/dataModels";

describe("testSlice", () => {
  // Freeze time so log timestamps are predictable
  beforeEach(() => {
    jest.useFakeTimers();
    jest.setSystemTime(new Date("2025-01-01T00:00:00.000Z"));
  });

  afterEach(() => {
    jest.useRealTimers();
    jest.restoreAllMocks();
  });

  it("startTestRequested adds the test and writes a start log", () => {
    const initialState = { tests: [], logs: [] };

    const test: Test = {
      testId: "t-1",
      testName: "Data Corruption Test",
      attuIp: "127.0.0.1",
      networkPort: 1234,
      port: "A" as any,
      status: "isRunning",
      message: "",
      dateTime: "2025-01-01T00:00:00.000Z",
      result: false,
    };

    const next = reducer(initialState, startTestRequested(test));

    expect(next.tests).toHaveLength(1);
    expect(next.tests[0]).toMatchObject({ testId: "t-1", testName: "Data Corruption Test" });

    expect(next.logs).toHaveLength(1);
    expect(next.logs[0]).toEqual({
      time: "2025-01-01T00:00:00.000Z",
      message: "Test Data Corruption Test with ID t-1 started.",
      type: "info",
    });
  });

  it("setTestResults updates an existing test and writes a 'Passed' log when result=true", () => {
    const initialState = {
      tests: [
        {
          testId: "t-2",
          testName: "Throughput",
          status: "isRunning",
          message: "",
          result: false,
        } as Test,
      ],
      logs: [],
    };

    const response: TestResponse = {
      testId: "t-2",
      status: "Passed",
      message: "OK",
      result: true,
    };

    const next = reducer(initialState, setTestResults(response));

    expect(next.tests[0]).toMatchObject({
      testId: "t-2",
      status: "Passed",
      message: "OK",
      result: true,
    });

    expect(next.logs).toHaveLength(1);
    expect(next.logs[0]).toEqual({
      time: "2025-01-01T00:00:00.000Z",
      message: "Throughput (ID: t-2): Passed",
      type: "success",
    });
  });

  it("setTestResults updates an existing test and writes a 'Failed' log when result=false", () => {
    const initialState = {
      tests: [
        {
          testId: "t-3",
          testName: "Stability",
          status: "isRunning",
          message: "",
          result: true,
        } as Test,
      ],
      logs: [],
    };

    const response: TestResponse = {
      testId: "t-3",
      status: "Failed",
      message: "Error",
      result: false,
    };

    const next = reducer(initialState, setTestResults(response));

    expect(next.tests[0]).toMatchObject({
      testId: "t-3",
      status: "Failed",
      message: "Error",
      result: false,
    });

    expect(next.logs).toHaveLength(1);
    expect(next.logs[0]).toEqual({
      time: "2025-01-01T00:00:00.000Z",
      message: "Stability (ID: t-3): Failed",
      type: "success",
    });
  });

  it("setTestResults does nothing if the testId is not found", () => {
    const initialState = {
      tests: [{ testId: "exists", testName: "X" } as Test],
      logs: [],
    };

    const response: TestResponse = {
      testId: "missing",
      status: "Failed",
      message: "OK",
      result: true,
    };

    const next = reducer(initialState, setTestResults(response));

    expect(next.tests).toHaveLength(1);
    expect(next.tests[0].testId).toBe("exists");
    expect(next.logs).toHaveLength(0);
  });

  it("removeTest removes the test with the given id", () => {
    const initialState = {
      tests: [
        { testId: "a", testName: "A" } as Test,
        { testId: "b", testName: "B" } as Test,
      ],
      logs: [],
    };

    const next = reducer(initialState, removeTest("a"));

    expect(next.tests.map((t) => t.testId)).toEqual(["b"]);
  });

  it("removeTest does nothing when id is not found", () => {
    const initialState = {
      tests: [{ testId: "a", testName: "A" } as Test],
      logs: [],
    };

    const next = reducer(initialState, removeTest("nope"));

    expect(next.tests).toHaveLength(1);
    expect(next.tests[0].testId).toBe("a");
  });
});

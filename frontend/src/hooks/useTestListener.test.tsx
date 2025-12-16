import { renderHook } from "@testing-library/react";
import { useTestListener } from "./useTestListener";
import { setTestResults } from "../store/slices/testSlice";

let mockLastJsonMessage: any = null;

jest.mock("./useAppWebSocket", () => ({
    useAppWebSocket: () => ({ lastJsonMessage: mockLastJsonMessage }),
}));

const mockDispatch = jest.fn();
jest.mock("react-redux", () => ({
    useDispatch: () => mockDispatch,
}));

describe("useTestListener", () => {
    beforeEach(() => {
        mockLastJsonMessage = null;
        mockDispatch.mockClear();
    });

    it("does nothing when lastJsonMessage is null", () => {
        renderHook(() => useTestListener());
        expect(mockDispatch).not.toHaveBeenCalled();
    });

    it("dispatches setTestResults when receiving a 'test-result' with status 'ok'", () => {
        mockLastJsonMessage = {
            type: "test-result",
            payload: { testId: "t-1", status: "ok", message: "Done", result: true },
        };

        renderHook(() => useTestListener());

        expect(mockDispatch).toHaveBeenCalledWith(
            setTestResults({ testId: "t-1", status: "ok", message: "Done", result: true })
        );
    });
});

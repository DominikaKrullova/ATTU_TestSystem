import { useEffect } from "react";
import { useAppWebSocket } from "./useAppWebSocket";
import { Test, TestResponse } from "../model/dataModels";
import { useDispatch } from "react-redux";
import { setTestResults } from "../store/slices/testSlice";

export function useTestListener() {
  const { lastJsonMessage } = useAppWebSocket();
  const dispatch = useDispatch();

  useEffect(() => {
    if (!lastJsonMessage) return;

    const { test_id, result } = lastJsonMessage as {
      test_id: string,
      result: boolean
        
    }

      const testResult: TestResponse = {
        testId: test_id,
        result: result
      };

      dispatch(setTestResults(testResult))
    
  }, [lastJsonMessage]);
}

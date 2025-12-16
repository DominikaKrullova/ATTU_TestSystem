import { createSlice, PayloadAction } from '@reduxjs/toolkit';
import { Logs, Test, TestResponse } from '../../model/dataModels';

interface TestState {
    tests: Test[];
    logs: Logs[];
}

const initialState: TestState = {
    tests: [],
    logs: [],
};


const testSlice = createSlice({
    name: 'test',
    initialState,
    reducers: {
        startTestRequested: (state, action: PayloadAction<Test>) => {
            state.tests.push(action.payload);
            state.logs.push({ time: new Date().toISOString(), message: `Test ${action.payload.testName} with ID ${action.payload.testId} started.`, type: 'info' });
        },
        setTestResults: (state, action: PayloadAction<TestResponse>) => {
        
            const response = action.payload;
            const test = state.tests.find((t) => t.testId === response.testId);
           
            if (test) {
                test.message = response.message;
                test.result = response.result;

                if(response.result){
                    test.status = "Passed"
                } else {
                    test.status = "Failed"
                }

                state.logs.push({
                    time: new Date().toISOString(),
                    message: `${test.testName} (ID: ${test.testId}): ${test.status}`,
                    type: test.status
                });
            }
        },
        removeTest: (state, action: PayloadAction<string>) => {
            const testId = state.tests.findIndex(t => t.testId === action.payload);
            if (testId !== -1) state.tests.splice(testId, 1);
        },
        clearLogs: (state) => {
      state.logs = [];
        },
        clearTests: (state) => {
      state.tests = [];
    },
    },
});

export const { startTestRequested, setTestResults, removeTest, clearLogs, clearTests } = testSlice.actions;
export default testSlice.reducer;


import { configureStore, combineReducers } from '@reduxjs/toolkit';
import storage from 'redux-persist/lib/storage';
import { persistReducer, persistStore } from 'redux-persist';

import attuReducer from './slices/attuSlice';
import testReducer from './slices/testSlice';

const rootReducer = combineReducers({
  attuReducer: attuReducer,
  testReducer: testReducer,
});

const persistConfig = {
  key: 'root',      
  storage,
  whitelist: ['attuReducer', 'testReducer'],
};

const persistedReducer = persistReducer(persistConfig, rootReducer);

export const store = configureStore({
  reducer: persistedReducer,
});
export type RootState = ReturnType<typeof store.getState>;
export const persistor = persistStore(store);

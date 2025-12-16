import React from 'react';
import { Route, Router, Routes } from 'react-router-dom';
import SideBar from './components/SideBar/SideBar';
import Tests from './pages/Tests';
import styles from './App.module.scss';
import ConfigPage from './pages/Config';
import Home from './pages/Home';
import { useAppWebSocket } from './hooks/useAppWebSocket';
import { useTestListener } from './hooks/useTestListener';

function App() {

  const { connectionStatus } = useAppWebSocket();
  useTestListener();

  return (
    <div className={styles.app}>
      <SideBar connectionStatus={connectionStatus} />
      <div className={styles.pageContainer}>
        <Routes>
          <Route path='/' element={<Home />} />
          <Route path='/config' element={<ConfigPage />} />
          <Route path='/tests' element={<Tests />} />
        </Routes>
      </div>
    </div>
  );
}

export default App;

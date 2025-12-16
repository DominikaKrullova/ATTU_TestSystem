import React from "react";
import type { Logs as LogsInterface } from "../../../model/dataModels";
import styles from "./Logs.module.scss";
import { useDispatch, useSelector } from "react-redux";
import { RootState } from "../../../store/store";
import { clearLogs } from "../../../store/slices/testSlice";
import classNames from "classnames";



export default function Logs() {

  const dispatch = useDispatch();

  function handleClear() {
    dispatch(clearLogs());
  }

  const logs = useSelector((state: RootState) => state.testReducer.logs);
  return (
    <div className={styles.logsPanel}>
      <div className={styles.header}>
        <h3>Logs</h3>
        <button className={styles.button} onClick={handleClear}>Clear</button>
      </div>
      <div className={styles.logsContainer}>
        {logs.map((log, index) => (
          <div
            key={index}
            className={classNames(styles.logText, {
              [styles.passed]: log.type === "Passed",
              [styles.failed]: log.type === "Failed",
            })}

          >
            [{log.time}] {log.message}
          </div>
        ))}
      </div>
    </div>
  );
}
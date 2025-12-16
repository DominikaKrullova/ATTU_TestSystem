import React, { useEffect, useState } from 'react'
import { RootState } from '../../../store/store'
import styles from './Queue.module.scss'
import { Test, TestStartRequest } from '../../../model/dataModels'
import { useSelector, useDispatch } from 'react-redux'
import { removeTest, clearTests } from "../../../store/slices/testSlice";
import { PdfButton } from '../../../components/PDFGenerator/pdfGenerator'
import classNames from 'classnames'

const Queue = () => {

  const testList = useSelector((state: RootState) => state.testReducer.tests);
  const dispatch = useDispatch();

  const handleRemove = (testId: string) => {
    dispatch(removeTest(testId))
  }

  function handleClear() {
    dispatch(clearTests());
  }

  return (
    <div className={styles.queuePanel}>
      <div className={styles.header}>
        <h3>Queue</h3>
        <div className={styles.queueButtons}>
          <PdfButton tests={testList}></PdfButton>
          <button className={styles.clearButton} onClick={handleClear}>Clear</button>
        </div>

      </div>
      <div className={styles.queueContainer}>
        <table className={styles.queueTable}>
          <thead>
            <tr>
              <th>Test Name</th>
              <th>ATTUIp</th>
              <th>Port</th>
              <th>Status</th>
              <th></th>
            </tr>
          </thead>

          <tbody>
            {testList?.map((test: Test) => (
              <tr key={test.testId}>
                <td>{test.testName}</td>
                <td>{test.attuIp}</td>
                <td>{test.port.portNumber}</td>
                <td>
                  <span
                    className={classNames(styles.status, {
                      [styles.passed]: test.status === "Passed",
                      [styles.failed]: test.status === "Failed",
                    })}
                  >
                    {test.status}
                  </span>
                </td>
                <td>
                  <button
                    className={styles.button}
                    onClick={() => handleRemove(test.testId)}
                  >
                    Remove
                  </button>
                </td>
              </tr>
            ))}
          </tbody>
        </table>
      </div>


    </div>
  )
}

export default Queue
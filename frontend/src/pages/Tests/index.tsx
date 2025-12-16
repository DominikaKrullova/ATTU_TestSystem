
import styles from './Tests.module.scss'
import Menu from './Menu'
import Queue from './Queue'
import Logs from './Logs'

const Tests = () => {
  return (
    <>
      <div>
        <h1>Tests</h1>
      </div>
      <div className={styles.pageContainer}>
        <div className={styles.testMenuAndList}>
          <Menu />
          <Queue />
        </div>
        <Logs />
      </div>


    </>
  )
}

export default Tests
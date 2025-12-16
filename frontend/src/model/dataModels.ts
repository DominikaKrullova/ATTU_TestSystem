export interface Port {
    id: string,
    portNumber: number,
    portConfig: PortConfig
}

export interface PortConfig {
    name: string,
    baudRate: number,
    parity: string,
    flowControl: boolean,
    dataBits: number,
    stopBits: number,
    protocol: string,
}

export interface ATTU {
    attuIp: string,
    networkPort: number,
    attuConfig: ATTUConfig,
    ports: Port[]
}

export interface ATTUConfig {
    gps: boolean,
}


export interface TestStartRequest {
    testId: string,
    testName: string,
    attuIp: string,
    networkPort: number,
    port: Port,
    status?: "isRunning" 
}


export interface TestStartResponse {
  testId: string;
  testName: string;
  attuIp: string;
  networkPort: number;
  port: Port;
  status?: 'Passed' | 'Failed' | 'info' | 'isRunning' | 'ok';
  message?: string;
  dateTime?: string;
}


export interface TestResponse {
  testId: string;
  status?: 'Passed' | 'Failed' | 'info' | 'isRunning' | 'ok';     
  message?: string;     
  result?: boolean;        
}



export interface Test {
    testId: string,
    testName: string,
    attuIp: string,
    port: Port,
    networkPort: number,
    result?: any,
    status?: 'Passed' | 'Failed' | 'info' | 'isRunning' | 'ok';
    dateTime?: string
    message?: string,
}

export interface Logs {
    time: string;
    message: string;
    type: 'Passed' | 'Failed' | 'info' | 'isRunning' | 'ok';
}

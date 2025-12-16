import { createSlice, PayloadAction } from '@reduxjs/toolkit';
import { ATTU, Port } from '../../model/dataModels';
import { v4 as uuidv4 } from 'uuid';

interface ATTUState {
  attus: ATTU[];
}

const initialState: ATTUState = {
  attus: [],
};

const createDefaultPorts = (): Port[] => {
  const ports: Port[] = [];
  for (let i = 1; i <= 24; i++) {
    ports.push({
      id: uuidv4(),
      portNumber: i,
      portConfig: {
        name: `Port ${i}`,
        baudRate: 9600,
        parity: 'none',
        flowControl: false,
        dataBits: 8,
        stopBits: 1,
        protocol: 'ASCII',
      },
    });
  }
  return ports;
};

const attuSlice = createSlice({
  name: 'attu',
  initialState,
  reducers: {
    addATTU: (state, action) => {
      const { attuIp, networkPort } = action.payload;

      state.attus.push({
        attuIp,
        networkPort,
        attuConfig: { gps: true},

        ports: createDefaultPorts(),
      });
    },

    updateATTUConfig: (state, action: PayloadAction<{ attuIp: string; config: ATTU['attuConfig'] }>) => {
      return {
        ...state,
        attus: state.attus.map((attu) =>
          attu.attuIp === action.payload.attuIp
            ? { ...attu, attuConfig: action.payload.config }
            : attu
        ),
      };
    },
    updatePort: (state, action: PayloadAction<{ attuIp: string; port: Port }>) => {
      return {
        ...state,
        attus: state.attus.map((attu) => {
          if (attu.attuIp !== action.payload.attuIp) return attu;
          return {
            ...attu,
            ports: attu.ports.map((p) =>
              p.id === action.payload.port.id ? { ...p, portConfig: action.payload.port.portConfig } : p
            ),
          };
        }),
      };

    },
  },
});

export const { addATTU, updateATTUConfig, updatePort } = attuSlice.actions;
export default attuSlice.reducer;


import useWebSocket, { ReadyState } from "react-use-websocket";

// const WS_URL = "ws://localhost:8080/ws";
// const WS_URL = `ws://${window.location.host}/ws`;
const WS_URL = `ws://10.7.7.125:8080/ws`;

export function useAppWebSocket() {
  const {
    sendJsonMessage,
    sendMessage,
    lastJsonMessage,
    lastMessage,
    readyState,
  } = useWebSocket(WS_URL, {
    share: true,                
    shouldReconnect: () => true,
    reconnectInterval: 3000,
  });

  const connectionStatus =
    {
      [ReadyState.CONNECTING]: "Connecting",
      [ReadyState.OPEN]: "Open",
      [ReadyState.CLOSING]: "Closing",
      [ReadyState.CLOSED]: "Closed",
      [ReadyState.UNINSTANTIATED]: "Uninstantiated",
    }[readyState];

  return {
    sendJsonMessage, 
    sendMessage,
    lastJsonMessage,
    lastMessage,
    readyState,
    connectionStatus,
  };
}


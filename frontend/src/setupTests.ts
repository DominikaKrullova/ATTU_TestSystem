import "@testing-library/jest-dom";
import { randomUUID } from "crypto";

if (!globalThis.crypto) {
  globalThis.crypto = {} as Crypto;
}

if (!globalThis.crypto.randomUUID) {
  (globalThis.crypto as any).randomUUID = randomUUID;
}

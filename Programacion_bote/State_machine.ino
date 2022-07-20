void State_machine() {
  if (signalLost) {
    // If there is no signal, the boat doesn't send any message
    digitalWrite(Selector, HIGH);
    colorWipe(strip1.Color(255,   0,   0), 0);    // Red
  }
  else 
  
  
            


  switch (state) {
    case 0: // Boat is disable
      break;
    case 1: // Radio control mode - Telemetry off
      break;
    case 2: // Radio control mode - Telemetry on
      break;
    case 3: // Computer control mode
      break;
  }
}

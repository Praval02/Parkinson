const int micPin = A0; // Microphone connected to analog pin A0
const int sampleWindow = 50; // Sample window width in milliseconds
unsigned int sample; // Variable to store analog input from microphone

void setup() {
  Serial.begin(9600); // Initialize serial communication at 9600 bps
}

void loop() {
  unsigned long startMillis = millis(); // Store the start time of the sample window
  unsigned int peakToPeak = 0; // Variable to store the peak-to-peak amplitude
  unsigned int signalMax = 0; // Variable to track the maximum signal level
  unsigned int signalMin = 1024; // Variable to track the minimum signal level

  // Collect data for the duration of sampleWindow milliseconds
  while (millis() - startMillis < sampleWindow) {
    sample = analogRead(micPin); // Read the analog input from the microphone
    if (sample < 1024) { // Ensure valid readings (within the range of analog input)
      if (sample > signalMax) {
        signalMax = sample; // Update signalMax if the current sample is higher
      }
      if (sample < signalMin) {
        signalMin = sample; // Update signalMin if the current sample is lower
      }
    }
  }
  
  // Calculate the peak-to-peak amplitude
  peakToPeak = signalMax - signalMin; // Max - min = peak-to-peak amplitude
  double volts = (peakToPeak * 5.0) / 1024.0; // Convert the peak-to-peak value to volts

  // Print the voltage value to the Serial Monitor for plotting
  Serial.println(volts);

  delay(50); // Delay before the next reading, adjust for smoother plotting
}

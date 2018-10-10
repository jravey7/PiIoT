#ifndef HTMLPAGE_H
#define HTMLPAGE_H

// This file was built using a java tool ConvertHTML2CStringHeader (https://github.com/jravey7/PiIoT under tools folder).

const char *htmlPage=
"\
<!DOCTYPE html><html>\n\
<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n\
<link rel=\"icon\" href=\"data:,\">\n\
\n\
<!-- //// CSS for styling -->\n\
<style> \n\
  html { \n\
    font-family: Helvetica; \n\
    display: inline-block; \n\
    margin: 0px auto; \n\
    text-align: center;\n\
  }\n\
\n\
  .button { \n\
    background-color: #195B6A;\n\
    border: none; \n\
    color: white; \n\
    padding: 16px 40px;\n\
    text-decoration: none; \n\
    font-size: 30px; \n\
    margin: 2px; \n\
    cursor: pointer;\n\
  }\n\
\n\
  .slider {\n\
      -webkit-appearance: none;\n\
      width: 100%;\n\
      height: 15px;\n\
      border-radius: 5px;\n\
      background: #d3d3d3;\n\
      outline: none;\n\
      opacity: 0.7;\n\
      -webkit-transition: .2s;\n\
      transition: opacity .2s;\n\
  }\n\
\n\
  .slider::-webkit-slider-thumb {\n\
      -webkit-appearance: none;\n\
      appearance: none;\n\
      width: 25px;\n\
      height: 25px;\n\
      border-radius: 50%; \n\
      background: #4CAF50;\n\
      cursor: pointer;\n\
  }\n\
\n\
  .slider::-moz-range-thumb {\n\
      width: 25px;\n\
      height: 25px;\n\
      border-radius: 50%;\n\
      background: #4CAF50;\n\
      cursor: pointer;\n\
  }\n\
</style>\n\
<!-- end CSS -->\n\
\n\
</head>\n\
\n\
<!-- //// HTML -->\n\
<body>\n\
  <h1>ESP8266 Web Server</h1>\n\
\n\
  <!-- servo slider -->\n\
  <div class=\"slidecontainer\">\n\
    <input type=\"range\" min=\"0\" max=\"200\" value=\"%d\" class=\"slider\" id=\"servoRange\">\n\
    <p>Servo degrees: <span id=\"degreeText\"></span>%d</p>\n\
  </div>\n\
\n\
  <!-- open blinds action button -->\n\
  <p><a href=\"/openBlinds\"><button class=\"button\">Open blinds</button></a></p>\n\
  <p><a href=\"#\" id=\"setOpenBlinds\" onclick=\"setOpenBlinds();\"><button class=\"button\">Set blinds open</button></a></p>\n\
  <p>Open setting: <span id=\"setOpenBlindsText\">%d</span></p>\n\
\n\
  <!-- close blinds action button -->\n\
  <p><a href=\"/closeBlinds\"><button class=\"button\">Close blinds</button></a></p>\n\
  <p><a href=\"#\" id=\"setCloseBlinds\" onclick=\"setCloseBlinds();\"><button class=\"button\">Set blinds closed</button></a></p>\n\
  <p>Close setting: <span id=\"setCloseBlindsText\"></span>%d</p>\n\
\n\
  <!-- formatters for the NIST time -->\n\
  <p>Local Time (24hr): %02d:%02d:%02d</p>\n\
\n\
  <!-- //// javascript -->\n\
  <script>\n\
    var slider = document.getElementById(\"servoRange\");\n\
    var textOutput = document.getElementById(\"degreeText\");\n\
    var setOpenBlindsHRef = document.getElementById(\"setOpenBlinds\");\n\
    var setCloseBlindsHRef = document.getElementById(\"setCloseBlinds\");\n\
    textOutput.innerHTML = slider.value;\n\
\n\
    slider.oninput = function() {\n\
      textOutput.innerHTML = this.value;\n\
    }\n\
\n\
  </script>\n\
\n\
  <!-- javascript for submitting open/close settings -->\n\
  <script>\n\
\n\
    function setOpenBlinds() {\n\
      setOpenBlindsText.innerHTML = slider.value;\n\
      setOpenBlindsHRef.href = '/setOpenBlinds=\"' + slider.value + '\"';\n\
    }\n\
\n\
    function setCloseBlinds() {\n\
      setCloseBlindsText.innerHTML = slider.value;\n\
      setCloseBlindsHRef.href = '/setCloseBlinds=\"' + slider.value + '\"';\n\
    }\n\
\n\
  </script>\n\
\n\
</body></html> \n\
";

#endif //HTMLPAGE_H
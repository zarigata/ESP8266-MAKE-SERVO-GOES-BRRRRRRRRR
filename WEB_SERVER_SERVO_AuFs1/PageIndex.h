const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
  <head>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
      html {
        font-family: Arial;
        display: inline-block;
        margin: 0px auto;
        text-align: center;
      }
      
      .slidecontainer {
        width: 100%;
      }

      .slider {
        -webkit-appearance: none;
        width: 50%;
        height: 15px;
        border-radius: 5px;
        background: #d3d3d3;
        outline: none;
        opacity: 0.7;
        -webkit-transition: .2s;
        transition: opacity .2s;
      }

      .slider:hover {
        opacity: 1;
      }

      .slider::-webkit-slider-thumb {
        -webkit-appearance: none;
        appearance: none;
        width: 25px;
        height: 25px;
        border-radius: 50%;
        background: #4CAF50;
        cursor: pointer;
      }

      .slider::-moz-range-thumb {
        width: 25px;
        height: 25px;
        border-radius: 50%;
        background: #4CAF50;
        cursor: pointer;
      }
      .button{
        background-color: white;
        border: solid 1px green;
        text-align: center;
      }
    </style>
  </head>
  <body>

    <h1>APOLLO EAGLE CAR AuFs3</h1>
    <br><br>
    <div class="slidecontainer">
      <input type="range" min="0" max="150" value="75" class="slider" id="myRange">
      <p>Value : <span id="demo"></span></p>
    </div>
    <div class="button-container">
      <button type="button" class"button" onclick="" >Frente</button>
      <input type="button" class"button" id="back" onclick="back">Tras</input>
    </div>
     <p> UwU </p>
     

    <script>
      function sendData(pos) {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
          if (this.readyState == 4 && this.status == 200) {
            console.log(this.responseText);
          }
        };
        xhttp.open("GET", "setPOS?servoPOS="+pos, true);
        xhttp.send();
      } 
      var slider = document.getElementById("myRange");
      var output = document.getElementById("demo");
      output.innerHTML = slider.value;

      slider.oninput = function() {
        output.innerHTML = this.value;
        sendData(output.innerHTML);
      }

      function back() {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
          if (this.readyState == 4 && this.status == 200) {
            console.log(this.responseText);
          }
        };
        xhttp.open("GET", "back", true);
        xhttp.send();
      }  
     
    </script>

  </body>
</html>
)=====";

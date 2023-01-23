// Declare the HTML page
const char *html = R""""(
<!DOCTYPE html>
<html>

<head>
  <title>POV Manager</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="icon" href="data:,">
</head>
<!-- Disable refresh-->
<body >
  <div class="container">
    <h1>Pov Manager</h1>
    <div class="table-container">
      <!--Table grid 8*5-->
      <table>
        <tr class="line">
          <td class="cell"></td>
          <td class="cell"></td>
          <td class="cell"></td>
          <td class="cell"></td>
          <td class="cell"></td>
          <td class="cell"></td>
          <td class="cell"></td>
          <td class="cell"></td>
        </tr>
        <tr class="line">
          <td class="cell"></td>
          <td class="cell"></td>
          <td class="cell"></td>
          <td class="cell"></td>
          <td class="cell"></td>
          <td class="cell"></td>
          <td class="cell"></td>
          <td class="cell"></td>
        </tr>
        <tr class="line">
          <td class="cell"></td>
          <td class="cell"></td>
          <td class="cell"></td>
          <td class="cell"></td>
          <td class="cell"></td>
          <td class="cell"></td>
          <td class="cell"></td>
          <td class="cell"></td>
        </tr>
        <tr class="line">
          <td class="cell"></td>
          <td class="cell"></td>
          <td class="cell"></td>
          <td class="cell"></td>
          <td class="cell"></td>
          <td class="cell"></td>
          <td class="cell"></td>
          <td class="cell"></td>
        </tr>
        <tr class="line">
          <td class="cell"></td>
          <td class="cell"></td>
          <td class="cell"></td>
          <td class="cell"></td>
          <td class="cell"></td>
          <td class="cell"></td>
          <td class="cell"></td>
          <td class="cell"></td>
        </tr>
      
      </table>
    </div>
    <div class="speed">
      <p>Vitesse de l'animation</p>
      <input type="range" min="100" max="100000" value="1000" step="500" class="slider">
      <p class="speed-value"></p>
    </div>
    <p>Changer les visuels</p>
    <div class="anim-container">
      <button class="anim-1">Animation 1</button>
      <button class="anim-2">Animation 2</button>
      <button class="anim-3">Animation 3</button>

    </div>
    <div class="on-off-param">
      <div class="checkbox-btn">
        <p>Allumer / Eteindre Lumières</p>
        <button>On</button>
      </div>
    </div>
    <div>
    </div>
  </div>
  <script>

    //-----------------Main Function declaration-----------------//

    // Fetch route /api/display/on or /api/display/off
    function displayOnOff(status) {
      // Fetch route GET /api/display/on or /api/display/off
      fetch(`/api/display/${status}`, {
        method: 'GET',
        headers: {
          'Content-Type': 'application/json',
        },
      })
        .then((response) => response.json())
        .then((data) => {
          console.log('Success:', data);
        })
        .catch((error) => {
          console.error('Error:', error);
        });
    }
    // Fetch rout GET api/display/animation/ + animation number
    function setAnimation(number) {
      apiRoute = '/api/display/' + number;
      fetch(apiRoute, {
        method: 'GET',
        headers: {
          'Content-Type': 'application/json',
        },
      })
        .then((response) => response.json())
        .then((data) => {
          console.log('Success:', data);
        })
        .catch((error) => {
          console.error('Error:', error);
        });
      
    }

    //-----------------On/Off Button-----------------//
    const onOffBtn = document.querySelector('.on-off-param button');
    onOffBtn.addEventListener('click', () => {
      if (onOffBtn.innerHTML === 'On') {
        onOffBtn.innerHTML = 'Off';
        displayOnOff('off');
      } else {
        onOffBtn.innerHTML = 'On';
        displayOnOff('on');
      }
    });

    //-----------------Animation Button-----------------//
    if (document.querySelector('.anim-1')) {
      const anim1Btn = document.querySelector('.anim-1');
      anim1Btn.addEventListener('click', () => {
        setAnimation(1);
      });
    }
    if (document.querySelector('.anim-2')) {
      const anim2Btn = document.querySelector('.anim-2');
      anim2Btn.addEventListener('click', () => {
        setAnimation(2);
      });
    }
    if (document.querySelector('.anim-3')) {
      const anim3Btn = document.querySelector('.anim-3');
      anim3Btn.addEventListener('click', () => {
        setAnimation(3);
      });
    }

    //-----------------Table manager-----------------//

    // On click on a cell, add or remove the class "active"
    const cells = document.querySelectorAll('.cell');
    cells.forEach((cell) => {
      cell.addEventListener('click', () => {
        cell.classList.toggle('active');
      });
    });

    // Check if the cell is active or not and store the result in an object like this {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
    function sendAnimationCells() {
      const cells = document.querySelectorAll('.cell');
      let cellsArray = [];
      cells.forEach((cell) => {
        if (cell.classList.contains('active')) {
          cellsArray.push(1);
        } else {
          cellsArray.push(0);
        }
      });
      // Fetch route GET /api/display/animation?animation= + cellsArray
      fetch(`/api/display/animation?animation=${cellsArray}`, {
        method: 'GET',
        headers: {
          'Content-Type': 'application/json',
        },
      })
        .then((response) => response.json())
        .then((data) => {
          console.log('Success:', data);
        })
        .catch((error) => {
          console.error('Error:', error);
        });

    }

    //----------------- Click watcher-----------------//
    // Wait 0.5sec after click to send the animation if the user click on multiple cells
    let clickTimer;
    cells.forEach((cell) => {
      cell.addEventListener('click', () => {
        clearTimeout(clickTimer);
        clickTimer = setTimeout(() => {
          sendAnimationCells();
        }, 800);
      });
    });

    //-----------------Speed Slider-----------------//
    const speedSlider = document.querySelector('.slider');
    const speedValue = document.querySelector('.speed-value');
    speedValue.innerHTML = speedSlider.value;
    speedSlider.oninput = function () {
      speedValue.innerHTML = this.value;
    };
    speedSlider.addEventListener('mouseup', () => {
      // Fetch route GET /api/display/speed?speed= + speedSlider.value
      fetch(`/api/animation?speed=${speedSlider.value}`, {
        method: 'GET',
        headers: {
          'Content-Type': 'application/json',
        },
      })
        .then((response) => response.json())
        .then((data) => {
          console.log('Success:', data);
        })
        .catch((error) => {
          console.error('Error:', error);
        });
    });



  </script>
  <style>
    body {
      font-family: sans-serif;
      color: white;
      background-color: rgb(19, 19, 19);
    }

    .container {
      display: flex;
      flex-direction: column;
      text-align: center;
      margin: auto;
      background-color: black;
      border-radius: 15px;
      height: 100vh;
    }

    ul {
      display: flex;
      flex-direction: column;
      align-items: center;
      padding: 0%;
    }

    ul li,
    button {
      list-style: none;
      background-color: rgb(83, 83, 83);
      padding: 10px 0 10px 0;
      width: 70%;
      border-radius: 5px;
      margin: 5px;
      border: none;
    }

    ul li:hover {
      background-color: rgb(126, 126, 126);
      transition: all 0.5s;
      cursor: pointer;
    }

    ul li.active {
      background-color: rgb(255, 255, 255);
      color: black;
    }


    .table-container {
      display: flex;
      flex-direction: column;
      align-items: center;
      margin: 10px;
    }

    td {
      width: 50px;
      height: 50px;
      border: 1px solid black;
      background-color: rgb(83, 83, 83);
    }
    td.active {
      background-color: rgb(255, 255, 255);
    }

    .line {
      display: flex;
      flex-direction: row;
    }
  </style>
</body>

</html>
`)"""";
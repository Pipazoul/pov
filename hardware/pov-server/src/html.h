// Declare the HTML page
const char *html = R""""(
<!DOCTYPE html>
<html>

<head>
  <title>POV Manager</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="icon" href="data:,">
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
  </style>
</head>

<body>
  <div class="container">
    <h1>Pov Manager</h1>
    <div class="table-container">
      <!--Table grid 8*5-->
    </div>
    <div class="anim-container">
      <ul>
        <li> Animation 1</li>
        <li> Animation 2</li>
        <li> Animation 3</li>
      </ul>
    </div>
    <div class="strobe-param">
      <div class="checkbox-btn">
        <button>Strobe</button>
      </div>
      <!--Add a slider from 1 to 100-->
      <input type="range" min="1" max="100" value="50" class="slider" id="myRange">
    </div>
    <div class="on-off-param">
      <div class="checkbox-btn">
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

    //-----------------Animation Buttons-----------------//
    const li = document.querySelectorAll('li');
    li.forEach((item) => {
      item.addEventListener('click', () => {
        li.forEach((item) => {
          item.classList.remove('active');
        });
        item.classList.add('active');
      });
    });

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

    


  </script>
</body>

</html>
`)"""";
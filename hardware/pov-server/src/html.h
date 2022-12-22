// Declare the HTML page
const char *html = R""""(
<!DOCTYPE html>
<html>
<head>
  <title>POV Manager</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="icon" href="data:,">
  <style>
    .container {
      display: flex;
      flex-direction: column;
      justify-content: center;
      text-align: center;
      width: 50%;
      margin: auto;
    }
    ul {
      display: flex;
      flex-direction: column;
      align-items: center;
    }
    ul li {
      list-style: none;
      background-color: grey;
      padding: 5px;
      width: 30%;
      border-radius: 5px;
      margin: 5px;
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
          <li>Animation 1</li>
          <li>Animation 2</li>
          <li>Animation 3</li>
      </ul>
    </div>
  </div>
</body>
</html>
`)"""";
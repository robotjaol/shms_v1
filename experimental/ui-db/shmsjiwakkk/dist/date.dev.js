"use strict";

function displayDateTime() {
  var date = new Date();
  var year = date.getFullYear();
  var month = String(date.getMonth() + 1).padStart(2, '0');
  var day = String(date.getDate()).padStart(2, '0');
  var hours = date.getHours();
  var minutes = date.getMinutes();
  var amPm = hours >= 12 ? 'PM' : 'AM';
  var formattedTime = "".concat(hours, ":").concat(minutes.toString().padStart(2, '0'), " ").concat(amPm);
  var formattedDate = "".concat(day, "-").concat(month, "-").concat(year);
  var dateTime = "".concat(formattedTime, " ").concat(formattedDate);
  document.getElementById("time-date").innerHTML = dateTime;
}

window.onload = displayDateTime;
displayDateTime();
setInterval(displayDateTime, 1000);
//# sourceMappingURL=date.dev.js.map

function displayDateTime() {
    const date = new Date();
    const year = date.getFullYear();
    const month = String(date.getMonth() + 1).padStart(2, '0'); 
    const day = String(date.getDate()).padStart(2, '0');  
  
    const hours = date.getHours();
    const minutes = date.getMinutes();
    const amPm = hours >= 12 ? 'PM' : 'AM'; 
  
    const formattedTime = `${hours}:${minutes.toString().padStart(2, '0')} ${amPm}`; 
    const formattedDate = `${day}-${month}-${year}`;
    
  
    const dateTime = `${formattedTime} ${formattedDate}`;
    document.getElementById("time-date").innerHTML = dateTime;
  }
  
  window.onload = displayDateTime;
  displayDateTime();
  setInterval(displayDateTime, 1000);

gsap.fromTo(
  ".loading-page",
  { opacity: 1 },
  {
    opacity: 0,
    display: "none",
    duration: 1.5,
    delay: 3.5,
  }
);

gsap.fromTo(
  ".logo-name",
  {
    y: 50,
    opacity: 0,
  },
  {
    y: 0,
    opacity: 1,
    duration: 2,
    delay: 0.5,
  });

  document.addEventListener('DOMContentLoaded', function() {
    console.log("Document loaded");
  
    setTimeout(function() {
        console.log("Redirecting to Google");
        window.location.href = 'home.php';
    }, 3000); // 4000 milliseconds = 4 seconds
  });

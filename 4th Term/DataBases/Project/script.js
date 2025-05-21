document.getElementById("clickMe").addEventListener("click", () => {
  document.getElementById("output").textContent = "Button clicked! 🚀";
});

// Example: Show an error
const errorDiv = document.getElementById('sqlError');
errorDiv.textContent = 'Syntax error near "FROM"';
errorDiv.style.display = 'inline-block'; // or 'block'

// To clear the error
errorDiv.textContent = '';
errorDiv.style.display = 'none';

document.getElementById('connectBtn').addEventListener('click', () => {
  const dbSelector = document.getElementById('dbSelector');
  const selectedDB = dbSelector.value;
  const dbStatus = document.getElementById('dbStatus');
  const sqlError = document.getElementById('sqlError');

  // Clear any ongoing fade
  sqlError.style.transition = 'none';         // cancel transition
  sqlError.style.opacity = '1';               // reset opacity
  sqlError.style.display = 'inline-block';    // make sure it's visible
  void sqlError.offsetWidth;                  // force reflow to restart animation
  sqlError.style.transition = 'opacity 1s ease';

  if (!selectedDB) {
    sqlError.textContent = '❌ Please select a database before connecting.';

    // Fade out after 5 seconds
    setTimeout(() => {
      sqlError.style.opacity = '0'; // start fading

      // After fade completes, hide and clear
      setTimeout(() => {
        sqlError.style.display = 'none';
        sqlError.textContent = '';
      }, 600); // match transition duration
    }, 3000);

    dbStatus.textContent = 'Not connected';
    return;
  }

  dbStatus.textContent = `Connected to ${selectedDB}`;
  sqlError.style.display = 'none'; // hide error if successful
});


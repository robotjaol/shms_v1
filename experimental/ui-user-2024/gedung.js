// script.js

// Inisialisasi scene, camera, dan renderer
const scene = new THREE.Scene();
const camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 0.1, 1000);
const renderer = new THREE.WebGLRenderer();
renderer.setSize(window.innerWidth, window.innerHeight);
document.body.appendChild(renderer.domElement);

// Tambahkan kontrol orbit untuk memutar dan memperbesar bangunan
const controls = new THREE.OrbitControls(camera, renderer.domElement);
controls.enableDamping = true;
controls.dampingFactor = 0.25;
controls.enableZoom = true;

// Membuat geometrik bangunan sederhana
const geometry = new THREE.BoxGeometry(1, 2, 1);
const material = new THREE.MeshBasicMaterial({ color: 0x00ff00 });
const building = new THREE.Mesh(geometry, material);
scene.add(building);

// Tambahkan pencahayaan
const light = new THREE.AmbientLight(0x404040); // soft white light
scene.add(light);

// Set posisi kamera
camera.position.z = 5;

// Fungsi untuk merespons resize window
window.addEventListener('resize', () => {
  camera.aspect = window.innerWidth / window.innerHeight;
  camera.updateProjectionMatrix();
  renderer.setSize(window.innerWidth, window.innerHeight);
});

// Animasi render loop
function animate() {
  requestAnimationFrame(animate);
  
  // Animasi rotasi bangunan
  building.rotation.x += 0.01;
  building.rotation.y += 0.01;
  
  controls.update(); // update kontrol orbit
  renderer.render(scene, camera);
}

animate();

A simple RPG dice roller in GameBoy. More an excuse to make some game than anything (seriously just roll the real dices :D )

Supported dices : 2, 4, 6, 8, 12, 20, 100.

![splash screen](resources/rpgdices_splash.png?raw=true "splash") ![ingame](resources/screenshot-ingame.png?raw=true "in game screen")

---


Powered by **https://github.com/nakardo/node-gameboy**!

<canvas id="frame" width="160" height="144"></canvas>
<div id="action-buttons">
    <input id="input" type="file" accept=".gb"></input>
    <button id="fullscreen">Fullscreen</button>
    <button id="rendering">Rendering Mode</button>
    <button id="pause">Pause / Resume</button>
    <button id="reset">Reset</button>
</div>
<script
    src="https://code.jquery.com/jquery-3.1.1.min.js"
    integrity="sha256-hVVnYaiADRTO2PzUGmuLJr8BLUSjGIZsDYGmIJLv2b8="
    crossorigin="anonymous"></script>
<script src="https://unpkg.com/node-gameboy/dist/gameboy.min.js"></script>

<script>
// localStorage.debug = '';

var gameboy = window.gameboy = new (window.Gameboy)();

// Render

var canvas = document.getElementById('frame');

var ctx = canvas.getContext('2d');
gameboy.gpu.on('frame', function (offcanvas) {
    ctx.drawImage(offcanvas, 0, 0);
});

// Load rom

fetch(new Request('rpgdice.gb'))
    .then(response => response.arrayBuffer())
    .then(function (buffer) {
        gameboy.loadCart(buffer);
        gameboy.start();
    });

// Buttons

function loadFile () {
    if (!this.files.length) return;

    var reader = new FileReader();
    reader.onloadend = function () {
        gameboy.loadCart(reader.result);
        gameboy.start();
    };
    reader.readAsArrayBuffer(this.files[0]);
}

function fullscreen () {
    (
        canvas.requestFullscreen ||
        canvas.mozRequestFullScreen ||
        canvas.webkitRequestFullscreen ||
        canvas.msRequestFullscreen
    )
    .call(canvas);
}

$('#input').change(loadFile);
$('#fullscreen').click(fullscreen);
$('#pause').click(function () { gameboy.pauseResume() });
$('#reset').click(function () { gameboy.reset() });
$('#rendering').click(function () { $('#frame').toggleClass('pixelated') });

// Joypad

$(document).keydown(function (e) { gameboy.joypad.keyDown(e.keyCode) });
$(document).keyup(function (e) { gameboy.joypad.keyUp(e.keyCode) });
</script>
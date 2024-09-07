// will connect node server to this server
const socket = io('http://localhost:8000', { transports : ['websocket'] }); // establishes a WebSocket connection to the server running at http://localhost:8000 using Socket.IO
const form = document.getElementById('send-container');
const messageInput = document.getElementById('messageInp');
const messageContainer = document.querySelector(".container"); // to put message to container
var audio = new Audio('ting.mp3');

const append = (message,position)=>{
    const messageElement = document.createElement('div');
    messageElement.innerText = message;
    messageElement.classList.add('message');
    messageElement.classList.add(position);
    messageContainer.append(messageElement);
    if(position == 'left')
    {
        audio.play();
    }
}

form.addEventListener('submit', (e)=>{
    e.preventDefault();
    const message = messageInput.value;
    append(`You: ${message}`, 'right');
    socket.emit('send', message); // 'send' implemented in nodejs server
    messageInput.value = '';
})

const name = prompt("Enter your name to join");
socket.emit('new-user-joined',name); // we created this in nodejs server

socket.on('user-joined', name=>{
    append(`${name} joined the chat`, 'right');
}) 

socket.on('receive', data=>{
    append(`${data.name}: ${data.message}`, 'left');
}) 

socket.on('left', name=>{
    append(`${name} left the chat`, 'left');
}) 
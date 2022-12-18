
const socket = io.connect(':9919')

console.log('socket.js: loaded scoket.io')

socket.on('state', (message)=>{
    switch(message){
        case 'home':
            window.location.href = '/'
            break;

        case 'idle':
            window.location.href = '/idle'
            break;

        case 'game':
            window.location.href = '/game'
            break;

        case 'end':
            window.location.href = '/won'
            break;
        default:
            console.log('message not recognised', message)
            break;
    }
})

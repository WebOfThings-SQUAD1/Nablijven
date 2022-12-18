
const app=()=>{
    const inp_pw = document.getElementById("input_password")
    inp_pw.focus()

    async function loadLogin(){
        function sleep(s = 0.1) {
            return new Promise(resolve => setTimeout(resolve, s * 1000));
        }
        const a = document.createElement('div')
        const img = document.createElement('img')
        a.id="ovl_load"
        img.id="ovl_img"
        a.appendChild(img)
        document.body.appendChild(a)

        
        setTimeout(()=>{
            window.location='/game'
        },4000)
    }
    
    
    function verify() {
        // you found me, good job
        const pw = 'partyvelde'
        var pass = inp_pw.value;
        if(pass=='') return
        if (pass === pw) {
            loadLogin()
        }else{
            inp_pw.value = ""
        }
    }
    

    function next(ev) {
        if (ev.key == "Enter") {
            verify();
        }
    }
    document.addEventListener("keyup", next)
}

app()

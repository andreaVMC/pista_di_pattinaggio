function aggiorna(){
    document.body.style.backgroundImage = "url(" + "IMG/neve.png" + ")";
    sleep(5000);
    window.location.reload();
}

function sleep(millis)
{
    var date = new Date();
    var curDate = null;
    do { curDate = new Date(); }
    while(curDate-date < millis);
}

function credits(){
    window.location.href='https://github.com/andreaVMC/';
}
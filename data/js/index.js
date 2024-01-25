function ChangezStatusCompacteur() 
{
    fetch('/ChangerStatusCompacteur', {
        method: 'PUT',
    })
    .then(response => {
        if (!response.ok) 
        {
            throw new Error('Network response was not ok');
        }
        console.log('Response status:', response.status);
        return response.text();
    })
    .then(data => {
        console.log('Data received:', data);
        if (data === 'actif' || data === 'repos') 
        {
            let button = document.getElementById("compacteurButton");
            let statusSpan = document.getElementById("status");
            button.innerHTML = data === 'actif' ? 'Desactiver le Compacteur' : 'Activer Le compacteur';
            statusSpan.innerHTML = data;
        } 
        else 
        {
            console.error('Invalid data received from the server:', data);
        }
    })
    .catch(error => {
        console.error('Fetch error:', error);
    });
}
function ConsultezCannettesComp()
{
    window.location.href = "http://192.168.4.1/ConsultezCanettes";
}
function ConsultezClientsRecu()
{
    window.location.href = "http://192.168.4.1/ConsultezClientMontantRecu";
}
function ConsultezAdresse()
{
    window.location.href = "http://192.168.4.1/ConsultezAdresse";
}
addEventListener('load', () => {
    // Make all images link themselves
    let imgs = document.body.querySelectorAll('img');
    for (let i = 0; i < imgs.length; i++) {
        imgs[i].onclick = () => { window.location = imgs[i].src; };
    }

    // Convert dates earlier than a week to relative ("2 days ago") 
    let date = document.body.querySelector('.date');
    if (date) {
        date.title = date.textContent;
        const t = new Date() - new Date(date.textContent);
        const days = t / 1000 / 60 / 60 / 24;
        if (days < 7) {
            if (days > 1) {
                if (days < 2) {
                    date.textContent = 'Yesterday';
                } else {
                    date.textContent = Math.floor(days) + ' days ago';
                }
            } else {
                date.textContent = 'Today';
            }
        }
    }
});

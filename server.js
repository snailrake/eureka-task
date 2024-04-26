const express = require('express');
const { validate } = require('./build/Release/winapi');

const app = express();
const port = 3000;

app.use(express.json());
app.use(express.static('public'));

app.post('/check', (req, res) => {
    const n = req.body.n;
    const v = validate(n);
    res.json({ m: v ? "Authorized" : "Unauthorized" });
});

app.listen(port, async () => {
    console.log(`Server is active at http://localhost:${port}/`);
    try {
        const open = (await import('open')).default;
        open(`http://localhost:${port}/`);
    } catch (error) {
        console.error('Failed to initiate browser:', error);
    }
});

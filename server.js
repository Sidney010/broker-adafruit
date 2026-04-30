const express = require("express");
const app = express();

let dados = []; // Armazenamento de memória

app.get("/sensor", (req, res) => {
    const { temp, hum } = res.query;

    if(!temp || !hum){
        return res.status(400).send("Dados inválidos");
    }

    const leitura = {
        temperatura: temp,
        umidade: hum,
        data: new Date()
    };

    dados.push(leitura);

    console.log(leitura);

    res.send("OK");

});

app.get("/dados", (req, res) => {
    res.json(dados);
});

const PORT = process.env.PORT || 3000;

app.listen(PORT, () =>{
    console.log("Cheguei até aqui ");
    console.log("Estou a suas ordens comandante... ");
    console.log(`Servidor rodando na porta ${PORT}`);
})
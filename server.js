require('dotenv').config(); // Load environment variables from .env file

const express = require('express');
const bodyParser = require('body-parser');
const admin = require('firebase-admin');

// Load the Firebase service account key from the path in the environment variable
const serviceAccount = require(process.env.FIREBASE_SERVICE_ACCOUNT);

admin.initializeApp({
  credential: admin.credential.cert(serviceAccount),
  databaseURL: process.env.FIREBASE_DATABASE_URL,
});

const db = admin.database();
const app = express();
app.use(bodyParser.json());

app.post('/data', (req, res) => {
  const data = req.body;
  db.ref('sensorData')
    .push(data)
    .then(() => res.status(200).send('Data saved successfully'))
    .catch((error) => res.status(500).send(error));
});

const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
  console.log(`Server is running on port ${PORT}`);
});

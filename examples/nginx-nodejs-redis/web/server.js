const os = require('os')
const express = require('express')
const { createClient } = require('redis')

async function startServer () {
  const app = express()

  const redisClient = createClient({
    url: 'redis://172.23.0.2:6379',
    socket: {
      reconnectStrategy: function (retries) {
        console.log(`Attempting to reconnect to Redis, attempt number: ${retries}`)
        if (retries > 20) {
          console.log('Too many attempts to reconnect. Redis connection was terminated')
          return new Error('Too many retries.')
        } else {
          return retries * 500
        }
      }
    }
  })

  redisClient.on('error', error => {
    console.error('Redis client error:', error)
  })

  await redisClient.connect()

  app.get('/', async (req, res) => {
    try {
      let numVisits = await redisClient.get('numVisits')
      numVisits = parseInt(numVisits) || 0
      numVisits++
      await redisClient.set('numVisits', numVisits.toString())
      res.send(`${os.hostname()}: Number of visits is: ${numVisits}\n`)
    } catch (err) {
      console.log(err)
      res.send('An error occurred')
    }
  })

  app.listen(5000, function () {
    console.log('Web application is listening on port 5000')
  })
}

startServer().catch(err => {
  console.error('Error starting server:', err)
})

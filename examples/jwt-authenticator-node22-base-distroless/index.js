import { serve } from '@hono/node-server'
import { Hono } from 'hono'
import { jwtVerify } from 'jose'

const app = new Hono()
const secret = new TextEncoder().encode(process.env.JWT_SECRET || 'change-me-in-production')

app.get('/health', (c) => c.text('ok'))

app.use('/protected/*', async (c, next) => {
  const auth = c.req.header('Authorization')
  if (!auth?.startsWith('Bearer ')) {
    return c.json({ error: 'missing token' }, 401)
  }
  try {
    const { payload } = await jwtVerify(auth.slice(7), secret)
    c.set('user', payload)
    await next()
  } catch {
    return c.json({ error: 'invalid token' }, 401)
  }
})

app.get('/protected/me', (c) => c.json({ user: c.get('user') }))

serve({ fetch: app.fetch, port: 3000 })

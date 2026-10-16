import { SignJWT } from 'jose'

const secret = new TextEncoder().encode('change-me-in-production')
const jwt = await new SignJWT({ user: 'test-user', role: 'admin' })
  .setProtectedHeader({ alg: 'HS256' })
  .sign(secret)

console.log(jwt)

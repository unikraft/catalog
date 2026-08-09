# Tor

[Tor](https://www.torproject.org/)

# Install keys

Do one of the following

## Copy the relay's keys (for existing relays)
See:
https://support.torproject.org/relay-operators/#relay-operators_upgrade-or-move

## Generate new keys (for new relays)

```console
sudo tor -User $(USER) --keygen --DataDirectory data
```

NOTE: If you want to run a bridge you have to copy the `pt_state` directory too

# Adjust the config

You *must* set

- `Nickname`
- `ContactInfo`
- `Address`
  - Deploy once to find out the domain name or set it in advance


# Run it

~ 1GB RAM should suffice, maybe 2GB is better

```
kraft cloud --metro fra0 deploy -p 443:443 -M 1024M .
```

Please don't run an exit node :)

# Links

 - [Tor Project](https://support.torproject.org/relay-operators/)
 - [Relay Operator Guide](https://support.torproject.org/relay-operators)

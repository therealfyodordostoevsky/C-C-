import subprocess
import urllib.request
import random
import sys

class NoBlocks(Exception): pass

def get_blocks():
    try:
        with urllib.request.urlopen("http://{?REDACTED?}/grab") as response:
            r = response.read().decode('utf-8')
            if '<html' in r.lower():
                raise NoBlocks
            return r.split()
    except Exception as e:
        print(f"Error while getting blocks: {e}")
        return []

def download_pdf(block, proxy=None):
    base_url = "http://www.jstor.org/stable/pdfplus/"
    url = f"{base_url}{block}.pdf?acceptTC=true"
    
    prefix = ['curl']
    if proxy:
        prefix.extend(['--socks5', proxy])

    cmd = prefix + ['-H', f"Cookie: TENACIOUS={random.random():.15f}", '-o', f'pdfs/{block}.pdf', url]
    subprocess.run(cmd, check=True)

if __name__ == "__main__":
    proxy_arg = sys.argv[1] if len(sys.argv) > 1 else None

    while True:
        blocks = get_blocks()
        for block in blocks:
            print(block)
            download_pdf(block, proxy_arg)
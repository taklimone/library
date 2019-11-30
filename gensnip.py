import json
from pathlib import Path

snippet = {}
for file in Path('.').glob('**/*.cpp'):
    if str(file).startswith('test'):
        continue
    name = file.stem
    snippet[name] = {}
    snippet[name]['description'] = name
    snippet[name]['prefix'] = name
    with open(file, 'rt') as fin:
        snippet[name]['body'] = [
            line for line in fin.read().splitlines()
            if not (line.startswith('#include') or line == 'using namespace std;')
        ]

with open('cpp.json', 'wt') as fout:
    json.dump(snippet, fout, indent=4, sort_keys=True)

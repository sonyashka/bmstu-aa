with open('data/novel.txt', 'r') as f:
    data = f.read().replace('\n', ' ')

data = data.split()
for i in range(len(data)):
    data[i] = data[i].replace(',', ', ')
    data[i] = data[i].replace('?', '? ')
    data[i] = data[i].replace('.', '. ')
    data[i] = data[i].replace('«', '« ')
    data[i] = data[i].replace('»', '» ')
    data[i] = data[i].replace('!', '! ')
    data[i] = data[i].replace(':', ': ')
    data[i] = data[i].replace(';', '; ')
    data[i] = data[i].replace('…', '… ')
    data[i] = data[i].replace('"', '" ')

print(len(data))

fw = open("data/novel_pretty.txt", 'w')
for i in range(len(data)):
    if data[i] != "-":
        fw.write(data[i] + " ")
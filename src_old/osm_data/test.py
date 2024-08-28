from loader import get_data_from_overpass as gdfo


data = gdfo(55.800, 37.645, 55.812, 37.666)

for f in data['features']:
    if f['geometry']['type'] != 'Point' and f['properties']['type'] == 'node':
        print(f)
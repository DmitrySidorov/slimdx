/*
* Copyright (c) 2007 SlimDX Group
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/
#include <windows.h>
#include <dinput.h>
#include <string>

#include "DirectInputErrorHandler.h"

#include "Enums.h"
#include "DeviceConstants.h"
#include "Properties.h"
#include "Guids.h"

namespace SlimDX
{
namespace DirectInput
{
	/* Unused.
	ObjectProperties::ObjectProperties( IDirectInputDevice8W* pointer, String^ name, Type^ dataFormat )
	{
		this->pointer = pointer;
		how = DIPH_BYOFFSET;

		obj = Marshal::OffsetOf( dataFormat, name ).ToInt32();
	}
	*/

	/* Unused.
	ObjectProperties::ObjectProperties( IDirectInputDevice8W* pointer, int value, bool isUsageCode )
	{
		this->pointer = pointer;

		if( isUsageCode )
			how = DIPH_BYUSAGE;
		else
			how = DIPH_BYID;

		obj = value;
	}
	*/

	int ObjectProperties::LowerRange::get()
	{
		DIPROPRANGE dip;
		HRESULT hr;
		dip.diph.dwSize = sizeof( DIPROPRANGE );
		dip.diph.dwHeaderSize = sizeof( DIPROPHEADER );
		dip.diph.dwObj = obj;
		dip.diph.dwHow = how;

		hr = pointer->GetProperty( DIPROP_RANGE, &dip.diph );
		DirectInputErrorHandler::TestForFailure( hr );

		if( FAILED( hr ) )
			return 0;

		return dip.lMin;
	}

	int ObjectProperties::UpperRange::get()
	{
		DIPROPRANGE dip;
		HRESULT hr;
		dip.diph.dwSize = sizeof( DIPROPRANGE );
		dip.diph.dwHeaderSize = sizeof( DIPROPHEADER );
		dip.diph.dwObj = obj;
		dip.diph.dwHow = how;

		hr = pointer->GetProperty( DIPROP_RANGE, &dip.diph );
		DirectInputErrorHandler::TestForFailure( hr );

		if( FAILED( hr ) )
			return 0;

		return dip.lMax;
	}

	void ObjectProperties::SetRange( int lowerRange, int upperRange )
	{
		DIPROPRANGE dip;
		HRESULT hr;
		dip.diph.dwSize = sizeof( DIPROPRANGE );
		dip.diph.dwHeaderSize = sizeof( DIPROPHEADER );
		dip.diph.dwObj = obj;
		dip.diph.dwHow = how;
		dip.lMin = lowerRange;
		dip.lMax = upperRange;

		hr = pointer->SetProperty( DIPROP_RANGE, &dip.diph );
		DirectInputErrorHandler::TestForFailure( hr );
	}

	Object^ ObjectProperties::ApplicationData::get()
	{
		DIPROPPOINTER dip;
		HRESULT hr;
		dip.diph.dwSize = sizeof( DIPROPPOINTER );
		dip.diph.dwHeaderSize = sizeof( DIPROPHEADER );
		dip.diph.dwObj = obj;
		dip.diph.dwHow = how;

		hr = pointer->GetProperty( DIPROP_APPDATA, &dip.diph );
		DirectInputErrorHandler::TestForFailure( hr );

		if( FAILED( hr ) || dip.uData == NULL )
			return nullptr;

		IntPtr pointer( reinterpret_cast<void*>( dip.uData ) );
		GCHandle handle = GCHandle::FromIntPtr( pointer );
		if( !handle.IsAllocated )
			return nullptr;

		Object^ obj =  handle.Target;
		handle.Free();
		return obj;
	}

	void ObjectProperties::ApplicationData::set( Object^ value )
	{
		DIPROPPOINTER dip;
		HRESULT hr;
		dip.diph.dwSize = sizeof( DIPROPPOINTER );
		dip.diph.dwHeaderSize = sizeof( DIPROPHEADER );
		dip.diph.dwObj = obj;
		dip.diph.dwHow = how;

		GCHandle handle = GCHandle::Alloc( value, GCHandleType::Pinned );
		dip.uData = reinterpret_cast<UINT_PTR>( handle.ToIntPtr( handle ).ToPointer() );

		hr = pointer->SetProperty( DIPROP_APPDATA, &dip.diph );
		DirectInputErrorHandler::TestForFailure( hr );

		handle.Free();
	}

	int ObjectProperties::DeadZone::get()
	{
		DIPROPDWORD dip;
		HRESULT hr;
		dip.diph.dwSize = sizeof( DIPROPDWORD );
		dip.diph.dwHeaderSize = sizeof( DIPROPHEADER );
		dip.diph.dwObj = obj;
		dip.diph.dwHow = how;

		hr = pointer->GetProperty( DIPROP_DEADZONE, &dip.diph );
		DirectInputErrorHandler::TestForFailure( hr );

		if( FAILED( hr ) )
			return 0;

		return dip.dwData;
	}

	void ObjectProperties::DeadZone::set( int value )
	{
		DIPROPDWORD dip;
		HRESULT hr;
		dip.diph.dwSize = sizeof( DIPROPDWORD );
		dip.diph.dwHeaderSize = sizeof( DIPROPHEADER );
		dip.diph.dwObj = obj;
		dip.diph.dwHow = how;
		dip.dwData = value;

		hr = pointer->SetProperty( DIPROP_DEADZONE, &dip.diph );
		DirectInputErrorHandler::TestForFailure( hr );
	}

	int ObjectProperties::Granularity::get()
	{
		DIPROPDWORD dip;
		HRESULT hr;
		dip.diph.dwSize = sizeof( DIPROPDWORD );
		dip.diph.dwHeaderSize = sizeof( DIPROPHEADER );
		dip.diph.dwObj = obj;
		dip.diph.dwHow = how;

		hr = pointer->GetProperty( DIPROP_GRANULARITY, &dip.diph );
		DirectInputErrorHandler::TestForFailure( hr );

		if( FAILED( hr ) )
			return 0;

		return dip.dwData;
	}

	int ObjectProperties::Saturation::get()
	{
		DIPROPDWORD dip;
		HRESULT hr;
		dip.diph.dwSize = sizeof( DIPROPDWORD );
		dip.diph.dwHeaderSize = sizeof( DIPROPHEADER );
		dip.diph.dwObj = obj;
		dip.diph.dwHow = how;

		hr = pointer->GetProperty( DIPROP_SATURATION, &dip.diph );
		DirectInputErrorHandler::TestForFailure( hr );

		if( FAILED( hr ) )
			return 0;

		return dip.dwData;
	}

	void ObjectProperties::Saturation::set( int value )
	{
		DIPROPDWORD dip;
		HRESULT hr;
		dip.diph.dwSize = sizeof( DIPROPDWORD );
		dip.diph.dwHeaderSize = sizeof( DIPROPHEADER );
		dip.diph.dwObj = obj;
		dip.diph.dwHow = how;
		dip.dwData = value;

		hr = pointer->SetProperty( DIPROP_SATURATION, &dip.diph );
		DirectInputErrorHandler::TestForFailure( hr );
	}

	int ObjectProperties::LogicalRange::get()
	{
		DIPROPDWORD dip;
		HRESULT hr;
		dip.diph.dwSize = sizeof( DIPROPDWORD );
		dip.diph.dwHeaderSize = sizeof( DIPROPHEADER );
		dip.diph.dwObj = obj;
		dip.diph.dwHow = how;

		hr = pointer->GetProperty( DIPROP_LOGICALRANGE, &dip.diph );
		DirectInputErrorHandler::TestForFailure( hr );

		if( FAILED( hr ) )
			return 0;

		return dip.dwData;
	}

	int ObjectProperties::PhysicalRange::get()
	{
		DIPROPDWORD dip;
		HRESULT hr;
		dip.diph.dwSize = sizeof( DIPROPDWORD );
		dip.diph.dwHeaderSize = sizeof( DIPROPHEADER );
		dip.diph.dwObj = obj;
		dip.diph.dwHow = how;

		hr = pointer->GetProperty( DIPROP_PHYSICALRANGE, &dip.diph );
		DirectInputErrorHandler::TestForFailure( hr );

		if( FAILED( hr ) )
			return 0;

		return dip.dwData;
	}

	DeviceProperties::DeviceProperties( IDirectInputDevice8W *pointer )
	{
		this->pointer = pointer;
	}

	String^ DeviceProperties::GetKeyName( Key key )
	{
		DIPROPSTRING dip;
		HRESULT hr;
		dip.diph.dwSize = sizeof( DIPROPSTRING );
		dip.diph.dwHeaderSize = sizeof( DIPROPHEADER );
		dip.diph.dwObj = DeviceConstantConverter::KeyToDIK( key );
		dip.diph.dwHow = DIPH_DEVICE;

		hr = pointer->GetProperty( DIPROP_KEYNAME, &dip.diph );
		DirectInputErrorHandler::TestForFailure( hr );

		if( FAILED( hr ) )
			return nullptr;

		return gcnew String( dip.wsz );
	}

	String^ DeviceProperties::PortDisplayName::get()
	{
		DIPROPSTRING dip;
		HRESULT hr;
		dip.diph.dwSize = sizeof( DIPROPSTRING );
		dip.diph.dwHeaderSize = sizeof( DIPROPHEADER );
		dip.diph.dwObj = 0;
		dip.diph.dwHow = DIPH_DEVICE;

		hr = pointer->GetProperty( DIPROP_GETPORTDISPLAYNAME, &dip.diph );
		DirectInputErrorHandler::TestForFailure( hr );

		if( FAILED( hr ) )
			return nullptr;

		return gcnew String( dip.wsz );
	}

	String^ DeviceProperties::InstanceName::get()
	{
		DIPROPSTRING dip;
		HRESULT hr;
		dip.diph.dwSize = sizeof( DIPROPSTRING );
		dip.diph.dwHeaderSize = sizeof( DIPROPHEADER );
		dip.diph.dwObj = 0;
		dip.diph.dwHow = DIPH_DEVICE;

		hr = pointer->GetProperty( DIPROP_INSTANCENAME, &dip.diph );
		DirectInputErrorHandler::TestForFailure( hr );

		if( FAILED( hr ) )
			return nullptr;

		return gcnew String( dip.wsz );
	}

	void DeviceProperties::InstanceName::set( String^ value )
	{
		DIPROPSTRING dip;
		HRESULT hr;
		dip.diph.dwSize = sizeof( DIPROPSTRING );
		dip.diph.dwHeaderSize = sizeof( DIPROPHEADER );
		dip.diph.dwObj = 0;
		dip.diph.dwHow = DIPH_DEVICE;

		WCHAR chars[260] = { NULL };
		for( int i = 0; i < value->Length; i++ )
			chars[i] = value[i];
		memcpy( dip.wsz, chars, sizeof( WCHAR ) * 260 );

		hr = pointer->SetProperty( DIPROP_INSTANCENAME, &dip.diph );
		DirectInputErrorHandler::TestForFailure( hr );
	}

	String^ DeviceProperties::ProductName::get()
	{
		DIPROPSTRING dip;
		HRESULT hr;
		dip.diph.dwSize = sizeof( DIPROPSTRING );
		dip.diph.dwHeaderSize = sizeof( DIPROPHEADER );
		dip.diph.dwObj = 0;
		dip.diph.dwHow = DIPH_DEVICE;

		hr = pointer->GetProperty( DIPROP_PRODUCTNAME, &dip.diph );
		DirectInputErrorHandler::TestForFailure( hr );

		if( FAILED( hr ) )
			return nullptr;

		return gcnew String( dip.wsz );
	}

	void DeviceProperties::ProductName::set( String^ value )
	{
		DIPROPSTRING dip;
		HRESULT hr;
		dip.diph.dwSize = sizeof( DIPROPSTRING );
		dip.diph.dwHeaderSize = sizeof( DIPROPHEADER );
		dip.diph.dwObj = 0;
		dip.diph.dwHow = DIPH_DEVICE;

		WCHAR chars[260] = { NULL };
		for( int i = 0; i < value->Length; i++ )
			chars[i] = value[i];
		memcpy( dip.wsz, chars, sizeof( WCHAR ) * 260 );

		hr = pointer->SetProperty( DIPROP_PRODUCTNAME, &dip.diph );
		DirectInputErrorHandler::TestForFailure( hr );
	}

	String^ DeviceProperties::TypeName::get()
	{
		DIPROPSTRING dip;
		HRESULT hr;
		dip.diph.dwSize = sizeof( DIPROPSTRING );
		dip.diph.dwHeaderSize = sizeof( DIPROPHEADER );
		dip.diph.dwObj = 0;
		dip.diph.dwHow = DIPH_DEVICE;

		hr = pointer->GetProperty( DIPROP_TYPENAME, &dip.diph );
		DirectInputErrorHandler::TestForFailure( hr );

		if( FAILED( hr ) )
			return nullptr;

		return gcnew String( dip.wsz );
	}

	String^ DeviceProperties::UserName::get()
	{
		DIPROPSTRING dip;
		HRESULT hr;
		dip.diph.dwSize = sizeof( DIPROPSTRING );
		dip.diph.dwHeaderSize = sizeof( DIPROPHEADER );
		dip.diph.dwObj = 0;
		dip.diph.dwHow = DIPH_DEVICE;

		hr = pointer->GetProperty( DIPROP_USERNAME, &dip.diph );
		DirectInputErrorHandler::TestForFailure( hr );

		if( FAILED( hr ) )
			return nullptr;

		return gcnew String( dip.wsz );
	}

	int DeviceProperties::GetKeyCode( Key key )
	{
		DIPROPDWORD dip;
		HRESULT hr;
		dip.diph.dwSize = sizeof( DIPROPDWORD );
		dip.diph.dwHeaderSize = sizeof( DIPROPHEADER );
		dip.diph.dwObj = DeviceConstantConverter::KeyToDIK( key );
		dip.diph.dwHow = DIPH_DEVICE;

		hr = pointer->GetProperty( DIPROP_SCANCODE, &dip.diph );
		DirectInputErrorHandler::TestForFailure( hr );

		if( FAILED( hr ) )
			return 0;

		return dip.dwData;
	}

	Object^ DeviceProperties::ApplicationData::get()
	{
		DIPROPPOINTER dip;
		HRESULT hr;
		dip.diph.dwSize = sizeof( DIPROPPOINTER );
		dip.diph.dwHeaderSize = sizeof( DIPROPHEADER );
		dip.diph.dwObj = 0;
		dip.diph.dwHow = DIPH_DEVICE;

		hr = pointer->GetProperty( DIPROP_APPDATA, &dip.diph );
		DirectInputErrorHandler::TestForFailure( hr );

		if( FAILED( hr ) || dip.uData == NULL )
			return nullptr;

		IntPtr pointer( reinterpret_cast<void*>( dip.uData ) );
		GCHandle handle = GCHandle::FromIntPtr( pointer );
		if( !handle.IsAllocated )
			return nullptr;

		Object^ obj = handle.Target;
		handle.Free();
		return obj;
	}

	void DeviceProperties::ApplicationData::set( Object^ value )
	{
		DIPROPPOINTER dip;
		HRESULT hr;
		dip.diph.dwSize = sizeof( DIPROPPOINTER );
		dip.diph.dwHeaderSize = sizeof( DIPROPHEADER );
		dip.diph.dwObj = 0;
		dip.diph.dwHow = DIPH_DEVICE;

		GCHandle handle = GCHandle::Alloc( value, GCHandleType::Pinned );
		dip.uData = reinterpret_cast<UINT_PTR>( handle.ToIntPtr( handle ).ToPointer() );

		hr = pointer->SetProperty( DIPROP_APPDATA, &dip.diph );
		DirectInputErrorHandler::TestForFailure( hr );

		handle.Free();
	}

	bool DeviceProperties::AutoCenter::get()
	{
		DIPROPDWORD dip;
		HRESULT hr;
		dip.diph.dwSize = sizeof( DIPROPDWORD );
		dip.diph.dwHeaderSize = sizeof( DIPROPHEADER );
		dip.diph.dwObj = 0;
		dip.diph.dwHow = DIPH_DEVICE;

		hr = pointer->GetProperty( DIPROP_AUTOCENTER, &dip.diph );
		DirectInputErrorHandler::TestForFailure( hr );

		if( dip.dwData == DIPROPAUTOCENTER_OFF )
			return false;
		else
			return true;
	}

	void DeviceProperties::AutoCenter::set( bool value )
	{
		DIPROPDWORD dip;
		HRESULT hr;
		dip.diph.dwSize = sizeof( DIPROPDWORD );
		dip.diph.dwHeaderSize = sizeof( DIPROPHEADER );
		dip.diph.dwObj = 0;
		dip.diph.dwHow = DIPH_DEVICE;

		if( value )
			dip.dwData = DIPROPAUTOCENTER_ON;
		else
			dip.dwData = DIPROPAUTOCENTER_OFF;

		hr = pointer->SetProperty( DIPROP_AUTOCENTER, &dip.diph );
		DirectInputErrorHandler::TestForFailure( hr );
	}

	DeviceAxisMode DeviceProperties::AxisMode::get()
	{
		DIPROPDWORD dip;
		HRESULT hr;
		dip.diph.dwSize = sizeof( DIPROPDWORD );
		dip.diph.dwHeaderSize = sizeof( DIPROPHEADER );
		dip.diph.dwObj = 0;
		dip.diph.dwHow = DIPH_DEVICE;

		hr = pointer->GetProperty( DIPROP_AXISMODE, &dip.diph );
		DirectInputErrorHandler::TestForFailure( hr );

		return static_cast<DeviceAxisMode>( dip.dwData );
	}

	void DeviceProperties::AxisMode::set( DeviceAxisMode value )
	{
		DIPROPDWORD dip;
		HRESULT hr;
		dip.diph.dwSize = sizeof( DIPROPDWORD );
		dip.diph.dwHeaderSize = sizeof( DIPROPHEADER );
		dip.diph.dwObj = 0;
		dip.diph.dwHow = DIPH_DEVICE;
		dip.dwData = static_cast<DWORD>( value );

		hr = pointer->SetProperty( DIPROP_AXISMODE, &dip.diph );
		DirectInputErrorHandler::TestForFailure( hr );
	}

	int DeviceProperties::BufferSize::get()
	{
		DIPROPDWORD dip;
		HRESULT hr;
		dip.diph.dwSize = sizeof( DIPROPDWORD );
		dip.diph.dwHeaderSize = sizeof( DIPROPHEADER );
		dip.diph.dwObj = 0;
		dip.diph.dwHow = DIPH_DEVICE;

		hr = pointer->GetProperty( DIPROP_BUFFERSIZE, &dip.diph );
		DirectInputErrorHandler::TestForFailure( hr );

		if( FAILED( hr ) )
			return 0;

		return dip.dwData;
	}

	void DeviceProperties::BufferSize::set( int value )
	{
		DIPROPDWORD dip;
		HRESULT hr;
		dip.diph.dwSize = sizeof( DIPROPDWORD );
		dip.diph.dwHeaderSize = sizeof( DIPROPHEADER );
		dip.diph.dwObj = 0;
		dip.diph.dwHow = DIPH_DEVICE;
		dip.dwData = value;

		hr = pointer->SetProperty( DIPROP_BUFFERSIZE, &dip.diph );
		DirectInputErrorHandler::TestForFailure( hr );
	}

	int DeviceProperties::DeadZone::get()
	{
		DIPROPDWORD dip;
		HRESULT hr;
		dip.diph.dwSize = sizeof( DIPROPDWORD );
		dip.diph.dwHeaderSize = sizeof( DIPROPHEADER );
		dip.diph.dwObj = 0;
		dip.diph.dwHow = DIPH_DEVICE;

		hr = pointer->GetProperty( DIPROP_DEADZONE, &dip.diph );
		DirectInputErrorHandler::TestForFailure( hr );

		if( FAILED( hr ) )
			return 0;

		return dip.dwData;
	}

	void DeviceProperties::DeadZone::set( int value )
	{
		DIPROPDWORD dip;
		HRESULT hr;
		dip.diph.dwSize = sizeof( DIPROPDWORD );
		dip.diph.dwHeaderSize = sizeof( DIPROPHEADER );
		dip.diph.dwObj = 0;
		dip.diph.dwHow = DIPH_DEVICE;
		dip.dwData = value;

		hr = pointer->SetProperty( DIPROP_DEADZONE, &dip.diph );
		DirectInputErrorHandler::TestForFailure( hr );
	}

	int DeviceProperties::ForceFeedbackGain::get()
	{
		DIPROPDWORD dip;
		HRESULT hr;
		dip.diph.dwSize = sizeof( DIPROPDWORD );
		dip.diph.dwHeaderSize = sizeof( DIPROPHEADER );
		dip.diph.dwObj = 0;
		dip.diph.dwHow = DIPH_DEVICE;

		hr = pointer->GetProperty( DIPROP_FFGAIN, &dip.diph );
		DirectInputErrorHandler::TestForFailure( hr );

		if( FAILED( hr ) )
			return 0;

		return dip.dwData;
	}

	void DeviceProperties::ForceFeedbackGain::set( int value )
	{
		DIPROPDWORD dip;
		HRESULT hr;
		dip.diph.dwSize = sizeof( DIPROPDWORD );
		dip.diph.dwHeaderSize = sizeof( DIPROPHEADER );
		dip.diph.dwObj = 0;
		dip.diph.dwHow = DIPH_DEVICE;
		dip.dwData = value;

		hr = pointer->SetProperty( DIPROP_FFGAIN, &dip.diph );
		DirectInputErrorHandler::TestForFailure( hr );
	}

	int DeviceProperties::MemoryLoad::get()
	{
		DIPROPDWORD dip;
		HRESULT hr;
		dip.diph.dwSize = sizeof( DIPROPDWORD );
		dip.diph.dwHeaderSize = sizeof( DIPROPHEADER );
		dip.diph.dwObj = 0;
		dip.diph.dwHow = DIPH_DEVICE;

		hr = pointer->GetProperty( DIPROP_FFLOAD, &dip.diph );
		DirectInputErrorHandler::TestForFailure( hr );

		if( FAILED( hr ) )
			return 0;

		return dip.dwData;
	}

	int DeviceProperties::Granularity::get()
	{
		DIPROPDWORD dip;
		HRESULT hr;
		dip.diph.dwSize = sizeof( DIPROPDWORD );
		dip.diph.dwHeaderSize = sizeof( DIPROPHEADER );
		dip.diph.dwObj = 0;
		dip.diph.dwHow = DIPH_DEVICE;

		hr = pointer->GetProperty( DIPROP_GRANULARITY, &dip.diph );
		DirectInputErrorHandler::TestForFailure( hr );

		if( FAILED( hr ) )
			return 0;

		return dip.dwData;
	}

	int DeviceProperties::JoystickId::get()
	{
		DIPROPDWORD dip;
		HRESULT hr;
		dip.diph.dwSize = sizeof( DIPROPDWORD );
		dip.diph.dwHeaderSize = sizeof( DIPROPHEADER );
		dip.diph.dwObj = 0;
		dip.diph.dwHow = DIPH_DEVICE;

		hr = pointer->GetProperty( DIPROP_JOYSTICKID, &dip.diph );
		DirectInputErrorHandler::TestForFailure( hr );

		if( FAILED( hr ) )
			return 0;

		return dip.dwData;
	}

	int DeviceProperties::Saturation::get()
	{
		DIPROPDWORD dip;
		HRESULT hr;
		dip.diph.dwSize = sizeof( DIPROPDWORD );
		dip.diph.dwHeaderSize = sizeof( DIPROPHEADER );
		dip.diph.dwObj = 0;
		dip.diph.dwHow = DIPH_DEVICE;

		hr = pointer->GetProperty( DIPROP_SATURATION, &dip.diph );
		DirectInputErrorHandler::TestForFailure( hr );

		if( FAILED( hr ) )
			return 0;

		return dip.dwData;
	}

	void DeviceProperties::Saturation::set( int value )
	{
		DIPROPDWORD dip;
		HRESULT hr;
		dip.diph.dwSize = sizeof( DIPROPDWORD );
		dip.diph.dwHeaderSize = sizeof( DIPROPHEADER );
		dip.diph.dwObj = 0;
		dip.diph.dwHow = DIPH_DEVICE;
		dip.dwData = value;

		hr = pointer->SetProperty( DIPROP_SATURATION, &dip.diph );
		DirectInputErrorHandler::TestForFailure( hr );
	}

	Guid DeviceProperties::ClassGuid::get()
	{
		DIPROPGUIDANDPATH dip;
		HRESULT hr;
		dip.diph.dwSize = sizeof( DIPROPGUIDANDPATH );
		dip.diph.dwHeaderSize = sizeof( DIPROPHEADER );
		dip.diph.dwObj = 0;
		dip.diph.dwHow = DIPH_DEVICE;

		hr = pointer->GetProperty( DIPROP_GUIDANDPATH, &dip.diph );
		DirectInputErrorHandler::TestForFailure( hr );

		if( FAILED( hr ) )
			return Guid::Empty;

		return Utilities::ConvertNativeGuid( dip.guidClass );
	}

	String^ DeviceProperties::InterfacePath::get()
	{
		DIPROPGUIDANDPATH dip;
		HRESULT hr;
		dip.diph.dwSize = sizeof( DIPROPGUIDANDPATH );
		dip.diph.dwHeaderSize = sizeof( DIPROPHEADER );
		dip.diph.dwObj = 0;
		dip.diph.dwHow = DIPH_DEVICE;

		hr = pointer->GetProperty( DIPROP_GUIDANDPATH, &dip.diph );
		DirectInputErrorHandler::TestForFailure( hr );

		if( FAILED( hr ) )
			return nullptr;

		return gcnew String( dip.wszPath );
	}

	int DeviceProperties::VendorId::get()
	{
		DIPROPDWORD dip;
		HRESULT hr;
		dip.diph.dwSize = sizeof( DIPROPDWORD );
		dip.diph.dwHeaderSize = sizeof( DIPROPHEADER );
		dip.diph.dwObj = 0;
		dip.diph.dwHow = DIPH_DEVICE;

		hr = pointer->GetProperty( DIPROP_VIDPID, &dip.diph );
		DirectInputErrorHandler::TestForFailure( hr );

		if( FAILED( hr ) )
			return 0;

		return LOWORD( dip.dwData );
	}

	int DeviceProperties::ProductId::get()
	{
		DIPROPDWORD dip;
		HRESULT hr;
		dip.diph.dwSize = sizeof( DIPROPDWORD );
		dip.diph.dwHeaderSize = sizeof( DIPROPHEADER );
		dip.diph.dwObj = 0;
		dip.diph.dwHow = DIPH_DEVICE;

		hr = pointer->GetProperty( DIPROP_VIDPID, &dip.diph );
		DirectInputErrorHandler::TestForFailure( hr );

		if( FAILED( hr ) )
			return 0;

		return HIWORD( dip.dwData );
	}

	int DeviceProperties::LowerRange::get()
	{
		DIPROPRANGE dip;
		HRESULT hr;
		dip.diph.dwSize = sizeof( DIPROPRANGE );
		dip.diph.dwHeaderSize = sizeof( DIPROPHEADER );
		dip.diph.dwObj = 0;
		dip.diph.dwHow = DIPH_DEVICE;

		hr = pointer->GetProperty( DIPROP_RANGE, &dip.diph );
		DirectInputErrorHandler::TestForFailure( hr );

		if( FAILED( hr ) )
			return 0;

		return dip.lMin;
	}

	int DeviceProperties::UpperRange::get()
	{
		DIPROPRANGE dip;
		HRESULT hr;
		dip.diph.dwSize = sizeof( DIPROPRANGE );
		dip.diph.dwHeaderSize = sizeof( DIPROPHEADER );
		dip.diph.dwObj = 0;
		dip.diph.dwHow = DIPH_DEVICE;

		hr = pointer->GetProperty( DIPROP_RANGE, &dip.diph );
		DirectInputErrorHandler::TestForFailure( hr );

		if( FAILED( hr ) )
			return 0;

		return dip.lMax;
	}

	void DeviceProperties::SetRange( int lowerRange, int upperRange )
	{
		DIPROPRANGE dip;
		HRESULT hr;
		dip.diph.dwSize = sizeof( DIPROPRANGE );
		dip.diph.dwHeaderSize = sizeof( DIPROPHEADER );
		dip.diph.dwObj = 0;
		dip.diph.dwHow = DIPH_DEVICE;
		dip.lMin = lowerRange;
		dip.lMax = upperRange;

		hr = pointer->SetProperty( DIPROP_RANGE, &dip.diph );
		DirectInputErrorHandler::TestForFailure( hr );
	}
}
}
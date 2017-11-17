type item = {
  title: string,
  completed: bool
};

type state = {items: list(item)};

let strElm = ReasonReact.stringToElement;

let component = ReasonReact.reducerComponent("TodoApp");

let newItem = () => {title: "Click a button", completed: true};

let make = (children) => {
  ...component,
  initialState: () => {items: [{title: "Hey, let's add some things!", completed: false}]},
  reducer: ((), _) => ReasonReact.NoUpdate,
  render: ({state: {items}}) => {
    let numItems = List.length(items);
    <div className="app">
      <div className="title">
        (strElm("What to do"))
        <button onClick=((evt) => Js.log("didn't do anything"))> (strElm("Add a thing")) </button>
      </div>
      <div className="items"> (strElm("Nothing")) </div>
      <div className="footer"> (strElm(string_of_int(numItems) ++ " items")) </div>
    </div>
  }
};
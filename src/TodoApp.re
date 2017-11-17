type item = {
  id: int,
  title: string,
  completed: bool
};

let str = ReasonReact.stringToElement;

module TodoItem = {
  let component = ReasonReact.statelessComponent("TodoItem");
  let make = (~item, children) => {
    ...component,
    render: (self) =>
      <div className="item">
        <input
          _type="checkbox"
          defaultChecked=(Js.Boolean.to_js_boolean(item.completed))
          /* TODO make interactive */
        />
        (str(item.title))
      </div>
  };
};

type state = {items: list(item)};

type action =
  | AddItem;

let component = ReasonReact.reducerComponent("TodoApp");

let lastId = ref(0);

let newItem = () => {
  lastId := lastId^ + 1;
  {id: lastId^, title: "Click a button", completed: true}
};

let make = (children) => {
  ...component,
  initialState: () => {items: [{id: 0, title: "Hey, let's add some things!", completed: false}]},
  reducer: (action, {items}) =>
    switch action {
    | AddItem => ReasonReact.Update({items: [newItem(), ...items]})
    },
  render: ({state: {items}, reduce}) => {
    let numItems = List.length(items);
    /* let todoItems = items; */
    let todoItems =
      items
      |> List.map((item) => <TodoItem key=(string_of_int(item.id)) item />)
      |> Array.of_list
      |> ReasonReact.arrayToElement;
    <div className="app">
      <div className="title">
        (str("What to do"))
        <button onClick=(reduce((_evt) => AddItem))> (str("Add Thing")) </button>
      </div>
      <div className="items"> todoItems </div>
      /* (ReasonReact.arrayToElement(Array.of_list(List.map((item) => <TodoItem item />, items)))) */
      /* <div className="items"> (strElm("Nothing")) </div> */
      <div className="footer"> (str(string_of_int(numItems) ++ " items")) </div>
    </div>
  }
};